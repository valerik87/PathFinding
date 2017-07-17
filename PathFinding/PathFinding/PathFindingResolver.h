#pragma once

#include <iostream>
#include <set>
#include <vector>
#include "ParserInput.h"



using namespace PathFindingStructs;
using namespace std;

class PathFindingResolver
{
public:
	PathFindingResolver():
		m_oPathFindingOutput()
	{};
	const PathFindingOutput* GetSolution(const PathFindingInput* const i_pPathFindingInput);
private:

	struct Node
	{
		Node():
			m_iPosition(-1),
			m_iWeight(-1)
		{};

		Node(int i_iPosition , int i_iWeight)
		{
			m_iPosition = i_iPosition;
			m_iWeight = i_iWeight;
		}

		/*		-1 this<other, 0 this=other, 1 else		*/
		int WeightCompare(const Node& other) const
		{
			if (m_iWeight < other.m_iWeight) return -1;
			else if (m_iWeight == other.m_iWeight) return 0;
			else return 1;
		}

		bool operator==(const Node& val) const
		{
			return this->m_iPosition == val.m_iPosition;
		}
		bool operator<(const Node& val) const
		{
			return this->m_iPosition < val.m_iPosition;
		}
		friend std::ostream & operator<<(std::ostream &os, Node const &m)
		{
			return os << "(" << m.m_iPosition << "," << m.m_iWeight << ")";
		}

		bool IsValid() const
		{
			return m_iPosition > -1 && m_iWeight > -1;
		}
		void Invalidate()
		{
			this->m_iPosition = -1;
			this->m_iWeight = -1;
		}

		

		int m_iPosition;
		int m_iWeight;
	};

	int		FindPath(const int i_iStartX, const int i_iStartY,
					const int i_iTargetX, const int i_iTargetY,
					const unsigned char* i_pMap, 
					const int i_iMapWidth, const int i_iMapHeight,
					int* i_pOutBuffer, const int i_iOutBufferSize);

	/*
	Starting from NodeToExplore search for a local min.
	-Found a single local min:
		- Add to solution ???
		- Explore him. Add its neighbour to NodeToExplore (update nodes already in but with a worst weight)
	-Found multiple sub optimal local min:
		- Explore all best sub-optimal. Add their neighbour to NodeToExplore, move sub-optimal in NodeExploredNotOptimal.
	*/
	void	ExplorationPhase();
	
	/*
	Before add a node in solution search sub-case:
	- Node come from a Node already in Solution(so optimum).
	- Node come from a Node in NodeExploredNotOptimal.
	*/
	void	AddToSolution(const Node& node);
	bool	IsTargetNode(const Node& node);

	inline void	SearchAroundNode(const Node& o_oNode, const int i_iMapWidth, const int i_iMapHeight, int i_iLengthFound, const unsigned char* i_pMap);
	void		SearchAroundPosition(int i_iNodeArrayIndex, const int i_iMapWidth, const int i_iMapHeight, int i_iLengthFound, const unsigned char* i_pMap);
	
	//Fill the vector with the feasable four neighborhood
	void	GetNeighborhood(vector<int>& o_vNeighborhood, const int i_iIndexA, const int i_iMapWidth, int i_iMapHeight) const;
	void	GetNeighbourNodeFromVectorNode(vector<Node>& o_vOutput, const vector<Node>& i_vInput) const;
	void	GetLesserWeightNode(Node* o_oNode ,set<Node>* o_oSetToSearch);
	void	GetSubOptimalNodes(vector<Node>* o_vSubOptimal);

	void	ManageNewNode(const Node& node);
	void	MoveNodeToExplore(vector<Node>* i_vNodeToMove);
	
	bool	IsNodeInSolution(const Node& i_oNode) const;
	bool	IsNodeInNeighborhood(const Node& i_oNodeIn, const Node& i_oNodeNeighbour) const;

	PathFindingInput		m_oPathfindingInput;
	PathFindingOutput		m_oPathFindingOutput;
	
	vector<Node>	m_vSolution;
	vector<Node>	m_vSolutionNotOptimus;
	set<Node>		m_vNodeToExplore;
	set<Node>		m_vNodeToExploreNotOptimal;
	Node			m_oLastNodeAdded;

	int				m_iStepLimit;
	int				m_iStepCounter;
	int				m_iTargetPosition;
	bool			m_bTargetFound;

	void			PrintNodeIn(const set<Node>* i_oSet) const;
	void			PrintNodeIn(const vector<Node>* i_oVec) const;

	int				m_iIterationCounter = 0; //TO REMOVE
};
