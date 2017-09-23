#include "PathFindingResolver.h"
#include "Logger.h"
#include "Utilities.h"
#include <algorithm>

const PathFindingOutput* PathFindingResolver::GetSolution(const PathFindingInput* const i_pPathFindingInput)
{
	Clear();	
	
	m_oPathFindingOutput.m_iSize = FindPath(i_pPathFindingInput);
	return &m_oPathFindingOutput;
}

/*
The function must return the length of the shortest path between Start and Target, or −1−1 if no such path exists.
If the shortest path is longer than nOutBufferSize, the calling function might either give up or choose to call FindPath again with a larger output buffer.
*/
int PathFindingResolver::FindPath
(
	const PathFindingInput* i_pPathFindingInput
)
{
	using namespace Utilities;
	using namespace std;

	//init default return and outputVariable with unfeasable values
	m_oPathFindingOutput.AllocArray((int)1);
	*m_oPathFindingOutput.At(0) = -1;
	
	//define end conditions
	m_iStepLimit = i_pPathFindingInput->iOutBufferSize;
	m_bTargetFound = false;

	GetArrayIndexFromGridIndex(&m_iTargetPosition, i_pPathFindingInput->iTargetX, i_pPathFindingInput->iTargetY, i_pPathFindingInput->iMapWidth, i_pPathFindingInput->iMapHeight);
	Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "TargetIndex at: %i", m_iTargetPosition);
	

	//From Start position need to get the list of adjacent obj;
	int iStartIndexA = -1;

	//1)Define StartNode and insert it in NodeToExplore
	GetArrayIndexFromGridIndex(&iStartIndexA, i_pPathFindingInput->iStartX, i_pPathFindingInput->iStartY, i_pPathFindingInput->iMapWidth, i_pPathFindingInput->iMapHeight);
	Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "StartIndex at: %i", iStartIndexA);

	Node StartNode(iStartIndexA, 0, iStartIndexA);
	m_vNodeToExplore.insert(StartNode);

	while (m_iStepCounter<m_iStepLimit && !m_bTargetFound)
	{
		ExplorationPhase(i_pPathFindingInput);
	}
	if (m_bTargetFound)
	{
		BackTrip();
		return m_oPathFindingOutput.m_iSize;
	}
	else
	{
		//NO SOLUTION FOUND
		return 0;
	}
}

void PathFindingResolver::ExplorationPhase(const PathFindingInput* i_pPathFindingInput)
{
	++m_iIterationCounter;

	Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "------------------------- ExplorationPhase (InSolution:%i ,Iteration: %i):\n Node in ToExplore: %i\n", m_iStepCounter, m_iIterationCounter, m_vNodeToExplore.size());
	PrintNodeIn(&m_vNodeToExplore);

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
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Founded a Node(%i,%i) in NodeToExplore with a local min weight./n", oMinWeight.m_iPosition, oMinWeight.m_iWeight);
		AddToSolution(i_pPathFindingInput,oMinWeight);

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
			GetNeighborhood(vNeighbourhood, oMinWeight.m_iPosition, i_pPathFindingInput->iMapWidth, i_pPathFindingInput->iMapWidth);

			/*
			Check if neighbours are valid, Set their parent.
			*/
			vector<Node> vNodeToMove;
			for_each(vNeighbourhood.begin(), vNeighbourhood.end(), [&](int index)
			{
				if (index != -1 && i_pPathFindingInput->pMap[index] == '1')
				{
					vNodeToMove.push_back(Node(index, oMinWeight.m_iWeight + 1, oMinWeight.m_iPosition));
				}
			}
			);

			/*
			Moves valid ones in Node to explore
			*/
			MoveNodeToExplore(&vNodeToMove);

			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Now in NodeToExplore : /n",m_vNodeToExplore.size());
			PrintNodeIn(&m_vNodeToExplore);
		}
		else
		{
			/*
			21A2)
			Founded the Target Node
			*/
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Target found!");
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
					Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Found target searching in NodeToExplore\n");
					AddToSolution(i_pPathFindingInput,node);
				}
			});

			if(!m_bTargetFound)
			{
				//Get the vector of node with best sub-optimal weight
				vector<Node> vSubOptimalNodes;
				GetSubOptimalNodes(&vSubOptimalNodes);

				if (vSubOptimalNodes.size() > 0)
				{
					Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Found more sub - optimal node with weight %i in NodeToExplore.\n", vSubOptimalNodes.at(0).m_iWeight);
					PrintNodeIn(&m_vNodeToExplore);

					//Add SubOptimal node found in ToExploreNotOptimal
					for_each(vSubOptimalNodes.begin(), vSubOptimalNodes.end(), [&](Node node) {
						m_vNodeToExploreNotOptimal.insert(node); 
					});

					//for each node in SubOptimal need to get its neighbours
					vector<Node> vAllNeighbours;
					vAllNeighbours.reserve(4 * vSubOptimalNodes.size());
					GetNeighbourNodeFromVectorNode(i_pPathFindingInput,vAllNeighbours, vSubOptimalNodes);
					Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Neighbours found:\n");
					PrintNodeIn(&vAllNeighbours);

					for_each(vAllNeighbours.begin(), vAllNeighbours.end(), [&](Node node)
					{
						ManageNewNode(node);
					}
					);

					//Delete from NodeToExplore,they have been moved from SubOptimal to NodeExploredNotOptimal
					for_each(vSubOptimalNodes.begin(), vSubOptimalNodes.end(), [&](Node node) {m_vNodeToExplore.erase(node); });

					Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Now in NodeToExplore:");
					PrintNodeIn(&m_vNodeToExplore);

					Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Now in NodeToExploreNotOptimal:");
					PrintNodeIn(&m_vNodeToExploreNotOptimal);
				}
			}
		}
		else
		{
			/*23A1: nothing founded */
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Can't found a node with min weight in NodeToExplore.");

			//there aren't more node to explore
			m_bTargetFound = true;
		}
	}
}
void PathFindingResolver::BackTrip()
{
	Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Back phase");

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
	m_oPathFindingOutput.m_iSize = m_vSolution.size() + m_vSolutionReverted.size();
	m_oPathFindingOutput.AllocArray(m_oPathFindingOutput.m_iSize);
	for (int i = 0; i < m_oPathFindingOutput.m_iSize; )
	{
		for_each(m_vSolution.begin(), m_vSolution.end(), [&](Node node)
		{
			*m_oPathFindingOutput.At(i) = node.m_iPosition;
			++i;
		});

		for_each(m_vSolutionReverted.rbegin(), m_vSolutionReverted.rend(), [&](Node node)
		{
			*m_oPathFindingOutput.At(i) = node.m_iPosition;
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

	Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "UpperPosIndex:%i ,RightPosIndex: %i,BottomPosIndex: %i,LeftPosIndex: %i", o_vNeighborhood.at(0), o_vNeighborhood.at(1), o_vNeighborhood.at(2), o_vNeighborhood.at(3));
}
void PathFindingResolver::GetNeighbourNodeFromVectorNode(const PathFindingInput* i_pPathFindingInput,vector<Node>& o_vOutput, const vector<Node>& i_vInput) const
{
	if (i_vInput.size() > 0)
	{
		for_each(i_vInput.begin(), i_vInput.end(), [&](Node node)
		{
			vector<int> vNeighbourhood;
			vNeighbourhood.reserve(4 * i_vInput.size());
			GetNeighborhood(vNeighbourhood, node.m_iPosition, i_pPathFindingInput->iMapWidth, i_pPathFindingInput->iMapWidth);

			for_each(vNeighbourhood.begin(), vNeighbourhood.end(), [&](int index)
			{
				if (index != -1 && i_pPathFindingInput->pMap[index] == '1')
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
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s is in solution.",node.ToChar());
			bFound = true;

			if (node.WeightCompare(SolutionNode) == -1)
			{
				Logger::GetInstance().Log(Logger::SEVERITY::ERR, Logger::CONTEXT::PATH_FINDING, "Found a node with better weight of one already in solution");
			}
		}
	}
	);

	for_each(m_vSolutionNotOptimus.begin(), m_vSolutionNotOptimus.end(), [&node, &bFound](Node SolutionNode)
	{
		if (node == SolutionNode && !bFound)
		{
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s is in solution not optimus.", node.ToChar());
			bFound = true;
		}
	}
	);

	for_each(m_vNodeToExplore.begin(), m_vNodeToExplore.end(), [&node, &bFound](Node toExplore)
	{
		if (node == toExplore  && !bFound)
		{
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s is in NodeToExplore.", node.ToChar());
			bFound = true;

			if (node.WeightCompare(toExplore) == -1)
			{
				Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s < %s, updated in NodeToExplore.", node.ToChar(),toExplore.ToChar());
				toExplore.m_iWeight = node.m_iWeight;
			}
		}
	}
	);

	for_each(m_vNodeToExploreNotOptimal.begin(), m_vNodeToExploreNotOptimal.end(), [&node, &bFound](Node NotOptimal)
	{
		if (node == NotOptimal  && !bFound)
		{
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s is in NodeToExploreNotOptimal.", node.ToChar());
			bFound = true;

			if (node.WeightCompare(NotOptimal) == -1)
			{
				Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s < %s, updated in NodeToExploreNotOptimal.", node.ToChar(), NotOptimal.ToChar());
				NotOptimal.m_iWeight = node.m_iWeight;
			}
		}
	}
	);

	if (!bFound)
	{
		m_vNodeToExplore.insert(node);
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Node %s  added to NodeToExplore.", node.ToChar());
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
void PathFindingResolver::AddToSolution(const PathFindingInput* i_pPathFindingInput, const Node& i_oNodeToAdd)
{

	//first time is always empty
	if (m_vSolution.empty())
	{
		m_vSolution.push_back(i_oNodeToAdd);
		++m_iStepCounter;
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Added at solution node(%i,%i,%i)", i_oNodeToAdd.m_iPosition, i_oNodeToAdd.m_iWeight, i_oNodeToAdd.m_iParent);
	}
	else
	{
		/*
		check is last node inserted is a neighbour of the node to insert now.
		- yes: can assume is coming from an optimum path, add it
		- no: store in SolutionNotOptimum
		*/
		if (IsNodeInNeighborhood(i_pPathFindingInput,m_vSolution.at(m_vSolution.size() - 1), i_oNodeToAdd))
		{
			m_vSolution.push_back(i_oNodeToAdd);
			++m_iStepCounter;
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Added at solution node(%i,%i,%i) because of its neighbour %i already in optimum.", i_oNodeToAdd.m_iPosition, i_oNodeToAdd.m_iWeight, i_oNodeToAdd.m_iParent, m_vSolution.at(m_vSolution.size() - 1).m_iPosition);
		}
		else
		{
			m_vSolutionNotOptimus.push_back(i_oNodeToAdd);
			Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "Added at SolutionNotOptimum node(%i,%i,%i)", i_oNodeToAdd.m_iPosition, i_oNodeToAdd.m_iWeight, i_oNodeToAdd.m_iParent);
		}
	}
	if (m_iStepCounter >= m_iStepLimit)
	{
		m_iStepLimit = (int)(m_iStepLimit*m_fStepLimitMultiplier);
		Logger::GetInstance().Log(Logger::SEVERITY::LOG, Logger::CONTEXT::PATH_FINDING, "ATTENTION: StepLimit increase to %i", m_iStepLimit);
	}
}


bool PathFindingResolver::IsNodeInNeighborhood(const PathFindingInput* i_pPathFindingInput,const Node& i_oNodeIn, const Node& i_oNodeNeighbour) const
{
	vector<int> vNeighbourhood;
	vNeighbourhood.reserve(4);
	GetNeighborhood(vNeighbourhood, i_oNodeNeighbour.m_iPosition, i_pPathFindingInput->iMapWidth, i_pPathFindingInput->iMapHeight);

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


bool PathFindingResolver::IsTargetNode(const Node& node)
{
	return node.m_iPosition == m_iTargetPosition;
}
void PathFindingResolver::PrintNodeIn(const set<Node>* i_oSet) const
{
	for_each(i_oSet->begin(), i_oSet->end(), [] (Node node) 
	{
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "(%i,%i,%i)/n", node.m_iPosition, node.m_iWeight,node.m_iParent);
	});
}
void PathFindingResolver::PrintNodeIn(const vector<Node>* i_oVec) const
{
	for_each(i_oVec->begin(), i_oVec->end(), [](Node node)
	{
		Logger::GetInstance().Log(Logger::SEVERITY::DEBUG, Logger::CONTEXT::PATH_FINDING, "(%i,%i,%i)/n", node.m_iPosition, node.m_iWeight, node.m_iParent);
	});
}


void PathFindingResolver::Clear()
{
	m_bTargetFound = false;
	m_iIterationCounter = 0;
	m_iStepCounter = 0;
	m_iStepLimit = -1;
	m_iTargetPosition = -1;
	m_oPathFindingOutput.Clear();
	m_oTarget.Invalidate();
	m_vNodeToExplore.clear();
	m_vNodeToExploreNotOptimal.clear();
	m_vSolution.clear();
	m_vSolutionNotOptimus.clear();
}
