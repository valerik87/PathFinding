#include "PathFindingResolver.h"
#include "Utilities.h"
#include <algorithm>

const PathFindingOutput* PathFindingResolver::GetSolution(const PathFindingInput* const i_pPathFindingInput)
{
	m_oPathfindingInput = i_pPathFindingInput;
	m_oPathFindingOutput.pOutBuffer = new int[m_oPathfindingInput.iOutBufferSize];
	
	m_oPathFindingOutput.iSize = FindPath
		(
			m_oPathfindingInput.iStartX,
			m_oPathfindingInput.iStartY,
			m_oPathfindingInput.iTargetX,
			m_oPathfindingInput.iTargetY,
			m_oPathfindingInput.pMap,
			m_oPathfindingInput.iMapWidth,
			m_oPathfindingInput.iMapHeight,
			m_oPathFindingOutput.pOutBuffer,
			m_oPathfindingInput.iOutBufferSize
		);

	return &m_oPathFindingOutput;
}

/*
The function must return the length of the shortest path between Start and Target, or −1−1 if no such path exists.
If the shortest path is longer than nOutBufferSize, the calling function might either give up or choose to call FindPath again with a larger output buffer.
*/
int PathFindingResolver::FindPath
(
	const int i_iStartX, const int i_iStartY,
	const int i_iTargetX, const int i_iTargetY,
	const unsigned char* i_pMap,
	const int i_iMapWidth, const int i_iMapHeight,
	int* i_pOutBuffer, const int i_iOutBufferSize
)
{
	using namespace Utilities;
	using namespace std;

	//init default return and outputVariable with unfeasable values
	int iLengthFound = -1;
	i_pOutBuffer[0] = iLengthFound;
	iLengthFound = 0;
	
	//define end conditions
	m_iStepLimit = i_iOutBufferSize;
	m_iStepCounter = 0;
	m_bTargetFound = false;

	m_iTargetPosition = -1;
	GetArrayIndexFromGridIndex(&m_iTargetPosition, i_iTargetX, i_iTargetY, i_iMapWidth, i_iMapHeight);
	cout << "TargetIndexA: " << m_iTargetPosition << '\n' << endl;

	//From Start position need to get the list of adjacent obj;
	int iStartIndexA = -1;

	//1)Define StartNode and insert it in NodeToExplore
	GetArrayIndexFromGridIndex(&iStartIndexA,i_iStartX, i_iStartY,i_iMapWidth,i_iMapHeight);
	cout << "StartIndexA: " << iStartIndexA << '\n' <<  endl;
	Node StartNode(iStartIndexA, iLengthFound, iStartIndexA);
	m_vNodeToExplore.insert(StartNode);

	while (m_iStepCounter<m_iStepLimit && !m_bTargetFound)
	{
		ExplorationPhase();
	}
	BackTrip();
	
	//TEST
	/*i_pOutBuffer[0] = 3;
	i_pOutBuffer[1] = 4;
	i_pOutBuffer[2] = 5;*/
	/*return 3;*/
	return m_oPathFindingOutput.iSize;
}

void PathFindingResolver::ExplorationPhase()
{
	cout << "-------------------------\nExplorationPhase (InSolution:" << m_iStepCounter << " ," << "Iteration: " << ++m_iIterationCounter << "):\nNode in ToExplore: " << m_vNodeToExplore.size() << "\t";
	PrintNodeIn(&m_vNodeToExplore);
	cout << endl;

	/*
	2) From NodeToExplore search if there is:
		21: founded a local minimum, node with lesser weight among all nodes in NodeToExplore
		22: founded more node with same weight among all nodes in NodeToExplore
		23: nothing founded
	*/
	Node oMinWeight;
	GetLesserWeightNode(&oMinWeight, &m_vNodeToExplore);
	if (oMinWeight.IsValid())
	{
		/*
		21A)
		-Founded a single local min :
		-Add to solution
		*/
		cout << "Founded a Node(" << oMinWeight.m_iPosition << "," << oMinWeight.m_iWeight << ")" << " in NodeToExplore with a local min weight." << endl;
		AddToSolution(oMinWeight);

		m_bTargetFound = IsTargetNode(oMinWeight);
		if (!m_bTargetFound)
		{
			/*
			21A1)
			Explore the single node because isn't the Target.
			Add/update its neighbours on NodeToExplore
			*/
			vector<int> vNeighbourhood;
			vNeighbourhood.reserve(4);
			GetNeighborhood(vNeighbourhood, oMinWeight.m_iPosition, m_oPathfindingInput.iMapWidth, m_oPathfindingInput.iMapWidth);

			/*
			Check if neighbours are valid, Set their parent.
			*/
			vector<Node> vNodeToMove;
			for_each(vNeighbourhood.begin(), vNeighbourhood.end(), [&](int index)
			{
				if (index != -1 && m_oPathfindingInput.pMap[index] == '1')
				{
					vNodeToMove.push_back(Node(index, oMinWeight.m_iWeight + 1, oMinWeight.m_iPosition));
				}
			}
			);

			/*
			Moves valid ones in Node to explore
			*/
			MoveNodeToExplore(&vNodeToMove);

			cout << "Now in NodeToExplore: ";
			PrintNodeIn(&m_vNodeToExplore);
			cout << endl;
		}
		else
		{
			/*
			21A2)
			Founded the Target Node
			*/
			cout << "Target found!" << endl;
			//Remove comment to let algorithm continue to backtrack phase */ 
			m_oTarget = oMinWeight;
			m_bTargetFound = true;
		}
	}
	else
	{
		if (m_vNodeToExplore.size() > 0)
		{
			/*
			22A1)
			Founded more node with same weight among all nodes in NodeToExplore
			*/

			//Before start to search SubOptimal beighbours, search if target Node is in NodeToExplore
			for_each(m_vNodeToExplore.begin(), m_vNodeToExplore.end(), [&](const Node& node)
			{
				if (IsTargetNode(node))
				{
					m_bTargetFound = true;
					m_oTarget = node;
					cout << "Found target searching in NodeToExplore" << endl;
					AddToSolution(node);
				}
			});

			if(!m_bTargetFound)
			{
				//Get the vector of node with best sub-optimal weight
				vector<Node> vSubOptimalNodes;
				GetSubOptimalNodes(&vSubOptimalNodes);

				if (vSubOptimalNodes.size() > 0)
				{
					cout << "Found more sub-optimal node with weight " << vSubOptimalNodes.at(0).m_iWeight << " in NodeToExplore." << endl;
					PrintNodeIn(&m_vNodeToExplore);

					//Add SubOptimal node found in ToExploreNotOptimal
					for_each(vSubOptimalNodes.begin(), vSubOptimalNodes.end(), [&](Node node) {
						m_vNodeToExploreNotOptimal.insert(node); 
					});

					//for each node in SubOptimal need to get its neighbours
					vector<Node> vAllNeighbours;
					vAllNeighbours.reserve(4 * vSubOptimalNodes.size());
					GetNeighbourNodeFromVectorNode(vAllNeighbours, vSubOptimalNodes);
					cout << "Neighbours found: " << endl;
					PrintNodeIn(&vAllNeighbours);

					for_each(vAllNeighbours.begin(), vAllNeighbours.end(), [&](Node node)
					{
						ManageNewNode(node);
					}
					);

					//Delete from NodeToExplore,they have been moved from SubOptimal to NodeExploredNotOptimal
					for_each(vSubOptimalNodes.begin(), vSubOptimalNodes.end(), [&](Node node) {m_vNodeToExplore.erase(node); });

					cout << "Now in NodeToExplore:" << endl;
					PrintNodeIn(&m_vNodeToExplore);

					cout << "Now in NodeToExploreNotOptimal:" << endl;
					PrintNodeIn(&m_vNodeToExploreNotOptimal);
				}
			}
		}
		else
		{
			/*23A1: nothing founded */
			cout << "Can't found a node with min weight in NodeToExplore." << endl;

			//there aren't more node to explore
			m_bTargetFound = true;
		}
	}
}

void PathFindingResolver::BackTrip()
{
	cout << "Back phase" << endl;

	vector<Node> m_vSolutionReverted;
	while (!m_oTarget.IsStartNode())
	{
		m_vSolutionReverted.push_back(m_oTarget);
		bool founded = false;
		for_each(m_vNodeToExploreNotOptimal.begin(), m_vNodeToExploreNotOptimal.end(), [&](Node node)
		{
			if (!founded && node.m_iPosition == m_oTarget.m_iParent)
			{
				m_oTarget = node;
				founded = true;
			}
		});

		for_each(m_vSolutionNotOptimus.begin(), m_vSolutionNotOptimus.end(), [&](Node node)
		{
			if (!founded && node.m_iPosition == m_oTarget.m_iParent)
			{
				m_oTarget = node;
				founded = true;
			}
		});

		for_each(m_vSolution.begin(), m_vSolution.end(), [&](Node node)
		{
			if (!founded && node.m_iPosition == m_oTarget.m_iParent)
			{
				m_oTarget = node;
				founded = true;
			}
		});
	}
	m_oPathFindingOutput.iSize = m_vSolution.size() + m_vSolutionReverted.size();
	for (int i = 0; i < m_oPathFindingOutput.iSize; )
	{
		for_each(m_vSolution.begin(), m_vSolution.end(), [&](Node node)
		{
			m_oPathFindingOutput.pOutBuffer[i] = node.m_iPosition;
			++i;
		});

		for_each(m_vSolutionReverted.rbegin(), m_vSolutionReverted.rend(), [&](Node node)
		{
			m_oPathFindingOutput.pOutBuffer[i] = node.m_iPosition;
			++i;
		});
	}
}

void PathFindingResolver::GetNeighborhood(vector<int>& o_vNeighborhood, int i_iIndexA, const int i_iMapWidth, const int i_iMapHeight) const
{
	using namespace Utilities;

	o_vNeighborhood.clear();
	o_vNeighborhood.push_back(GetUpIndexFromArrayIndex(i_iIndexA, i_iMapWidth));
	o_vNeighborhood.push_back(GetRightIndexFromArrayIndex(i_iIndexA, i_iMapWidth, i_iMapHeight));
	o_vNeighborhood.push_back(GetBottomIndexFromArrayIndex(i_iIndexA, i_iMapWidth, i_iMapHeight));
	o_vNeighborhood.push_back(GetLeftIndexFromArrayIndex(i_iIndexA, i_iMapWidth, i_iMapHeight));

	/*cout << "UpperPosIndex: " << o_vNeighborhood.at(0) << endl;
	cout << "RightPosIndex: " << o_vNeighborhood.at(1) << endl;
	cout << "LeftPosIndex: " << o_vNeighborhood.at(3) << endl;
	cout << "BottomPosIndex: " << o_vNeighborhood.at(2) << endl;*/

}

void PathFindingResolver::GetNeighbourNodeFromVectorNode(vector<Node>& o_vOutput, const vector<Node>& i_vInput) const
{
	if (i_vInput.size() > 0)
	{
		for_each(i_vInput.begin(), i_vInput.end(), [&](Node node)
		{
			vector<int> vNeighbourhood;
			vNeighbourhood.reserve(4 * i_vInput.size());
			GetNeighborhood(vNeighbourhood, node.m_iPosition, m_oPathfindingInput.iMapWidth, m_oPathfindingInput.iMapWidth);

			for_each(vNeighbourhood.begin(), vNeighbourhood.end(), [&](int index)
			{
				if (index != -1 && m_oPathfindingInput.pMap[index] == '1')
				{
					o_vOutput.push_back(Node(index, node.m_iWeight + 1, node.m_iPosition));
				}
			});
		});
	}
}

void PathFindingResolver::GetLesserWeightNode(Node* o_oNode, set<Node>* o_oSetToSearch)
{
	int iWeightFound = INT_MAX;
	for (set<Node>::iterator it = o_oSetToSearch->begin();it != o_oSetToSearch->end(); ++it)
	{
		if (it->m_iWeight < iWeightFound)
		{
			o_oNode->m_iPosition = it->m_iPosition;
			o_oNode->m_iWeight = it->m_iWeight;
			o_oNode->m_iParent = it->m_iParent;
			iWeightFound = it->m_iWeight;
		}
		else
		{
			if (it->m_iWeight == iWeightFound)
			{
				o_oNode->Invalidate();
				break;
			}
		}
	}

	if (o_oNode != nullptr)
	{
		o_oSetToSearch->erase(*o_oNode);
	}
}

void PathFindingResolver::GetSubOptimalNodes(vector<Node>* o_vSubOptimal)
{
	int iBestSubOptimalWeight = INT_MAX;
	for_each(m_vNodeToExplore.begin(), m_vNodeToExplore.end(), [&iBestSubOptimalWeight,o_vSubOptimal](Node oNode)
	{
		if (oNode.m_iWeight < iBestSubOptimalWeight)
		{
			iBestSubOptimalWeight = oNode.m_iWeight;
			o_vSubOptimal->clear();
			o_vSubOptimal->push_back(oNode);
		}
		else
		{
			if (oNode.m_iWeight == iBestSubOptimalWeight)
			{
				o_vSubOptimal->push_back(oNode);
			}
		}
	}
	);
}

void PathFindingResolver::ManageNewNode(const Node& node)
{
	bool bFound = false;
	for_each(m_vSolution.begin(), m_vSolution.end(), [&node,&bFound](Node SolutionNode)
	{
		if (node == SolutionNode && !bFound)
		{
			cout << "Node" << node << " is in solution." << endl;
			bFound = true;

			if (node.WeightCompare(SolutionNode) == -1)
			{
				cout << "PROBLEM_PROBLEM Found a node with better weight of one already in solution PROBLEM_PROBLEM" << endl;
			}
		}
	}
	);

	for_each(m_vSolutionNotOptimus.begin(), m_vSolutionNotOptimus.end(), [&node, &bFound](Node SolutionNode)
	{
		if (node == SolutionNode && !bFound)
		{
			cout << "Node" << node << " is in solution not optimus." << endl;
			bFound = true;
		}
	}
	);

	for_each(m_vNodeToExplore.begin(), m_vNodeToExplore.end(), [&node, &bFound](Node toExplore)
	{
		if (node == toExplore  && !bFound)
		{
			cout << "Node" << node << " is in NodeToExplore." << endl;
			bFound = true;

			if (node.WeightCompare(toExplore) == -1)
			{
				cout << node << " < " << toExplore << " updated in NodeToExplore" << endl;
				toExplore.m_iWeight = node.m_iWeight;
			}
		}
	}
	);

	for_each(m_vNodeToExploreNotOptimal.begin(), m_vNodeToExploreNotOptimal.end(), [&node, &bFound](Node NotOptimal)
	{
		if (node == NotOptimal  && !bFound)
		{
			cout << "Node" << node << " is in NodeToExploreNotOptimal." << endl;
			bFound = true;

			if (node.WeightCompare(NotOptimal) == -1)
			{
				cout << node << " < " << NotOptimal << " updated in NodeToExploreNotOptimal" << endl;
				NotOptimal.m_iWeight = node.m_iWeight;
			}
		}
	}
	);

	if (!bFound)
	{
		m_vNodeToExplore.insert(node);
		cout << node << " added to NodeToExplore." << endl;
	}
}
void PathFindingResolver::MoveNodeToExplore(vector<Node>* o_vNodeToMove)
{
	for (vector<Node>::iterator it = o_vNodeToMove->begin(); it != o_vNodeToMove->end(); ++it)
	{
		set<Node>::iterator NodeFounded = m_vNodeToExplore.find(*it);
		if (NodeFounded != m_vNodeToExplore.end())
		{
			//if node is already contained in NodeToExplore, update the weight with the lesser one of them two.
			if (it->m_iWeight < NodeFounded->m_iWeight)
			{
				m_vNodeToExplore.erase(NodeFounded);
				m_vNodeToExplore.emplace(*it);
			}
		}
		else
		{
			m_vNodeToExplore.emplace(*it);
		}
	}
}


bool PathFindingResolver::IsNodeInNeighborhood(const Node& i_oNodeIn, const Node& i_oNodeNeighbour) const
{
	vector<int> vNeighbourhood;
	vNeighbourhood.reserve(4);
	GetNeighborhood(vNeighbourhood, i_oNodeNeighbour.m_iPosition, m_oPathfindingInput.iMapWidth, m_oPathfindingInput.iMapHeight);

	bool bFound = false;
	for_each(vNeighbourhood.begin(), vNeighbourhood.end(), [&](int iNeighbourPosition)
	{
		if (i_oNodeIn.m_iPosition == iNeighbourPosition) bFound = true;
	}
	);
	return bFound;
}

bool PathFindingResolver::IsNodeInSolution(const Node& i_oNode) const
{
	for_each(m_vSolution.begin(), m_vSolution.end(), [&](Node node)
	{
		if (node.m_iPosition == i_oNode.m_iPosition)
		{
			return true;
		}
	});
	return false;
}


void PathFindingResolver::AddToSolution(const Node& i_oNodeToAdd)
{

	//first time is always empty
	if (m_vSolution.empty())
	{
		m_vSolution.push_back(i_oNodeToAdd);
		m_oLastNodeAdded = i_oNodeToAdd;
		++m_iStepCounter;
		cout << "Added at solution node (" << i_oNodeToAdd.m_iPosition << "," << i_oNodeToAdd.m_iWeight << i_oNodeToAdd.m_iParent << ")" << endl;
		return;
	}

	/*
	check is last node inserted is a neighbour of the node to insert now.
	- yes: can assume is coming from an optimum path, add it
	- no: store in SolutionNotOptimum
	*/
	if (IsNodeInNeighborhood(m_vSolution.at(m_vSolution.size() - 1), i_oNodeToAdd))
	{

		m_vSolution.push_back(i_oNodeToAdd);
		m_oLastNodeAdded = i_oNodeToAdd;
		++m_iStepCounter;
		cout << "Added at solution node(" << i_oNodeToAdd.m_iPosition << "," << i_oNodeToAdd.m_iWeight << "," << i_oNodeToAdd.m_iParent << ") because of its neighbour " << m_vSolution.at(m_vSolution.size() - 1).m_iPosition << " already in optimum" << endl;
		return;
	}
	else
	{
		m_vSolutionNotOptimus.push_back(i_oNodeToAdd);
		cout << "Added at SolutionNotOptimum node(" << i_oNodeToAdd.m_iPosition << "," << i_oNodeToAdd.m_iWeight << "," << i_oNodeToAdd.m_iParent << ")" << endl;
	}
}

bool PathFindingResolver::IsTargetNode(const Node& node)
{
	return node.m_iPosition == m_iTargetPosition;
}


void PathFindingResolver::PrintNodeIn(const set<Node>* i_oSet) const
{
	for_each(i_oSet->begin(), i_oSet->end(), [] (Node node) 
	{
		cout << "(" << node.m_iPosition << "," << node.m_iWeight << "," << node.m_iParent << ")";
	});
	cout << endl;
}

void PathFindingResolver::PrintNodeIn(const vector<Node>* i_oVec) const
{
	for_each(i_oVec->begin(), i_oVec->end(), [](Node node)
	{
		cout << "(" << node.m_iPosition << "," << node.m_iWeight << "," << node.m_iParent << ")";
	});
	cout << endl;
}

