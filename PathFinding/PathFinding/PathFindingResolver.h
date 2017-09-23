#pragma once

#include <iostream>
#include <set>
#include <sstream>
#include <vector>
#include "ParserInput.h"

using namespace PathFindingStructs;
using namespace std;

class PathFindingResolver
{
public:
	PathFindingResolver() :
		m_iIterationCounter(-1),
		m_iStepCounter(0),
		m_iStepLimit(-1),
		m_iTargetPosition(-1),
		m_oPathFindingOutput()
	{};
	const PathFindingOutput* GetSolution(const PathFindingInput* const i_pPathFindingInput);
private:

	struct Node
	{
		Node():
			m_iPosition(-1),
			m_iWeight(-1),
			m_iParent(-1)
		{};

		Node(int i_iPosition , int i_iWeight, int i_iParent)
		{
			m_iPosition = i_iPosition;
			m_iWeight = i_iWeight;
			m_iParent = i_iParent;
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
		/*friend std::ostream & operator<<(std::ostream &os, Node const &m)
		{
			return os << "(" << m.m_iPosition << "," << m.m_iWeight << "," << m.m_iParent << ")";
		}*/

		const char* ToChar() const
		{
			char toChar[25];
			sprintf_s(toChar, "(%i,%i,%i)", m_iPosition, m_iWeight, m_iParent);
			return toChar;
		}

		bool IsValid() const
		{
			return m_iPosition > -1 && m_iWeight > -1 && m_iParent > -1;
		}
		void Invalidate()
		{
			this->m_iPosition = -1;
			this->m_iWeight = -1;
			this->m_iParent = -1;
		}

		bool IsStartNode()
		{
			return m_iPosition == m_iParent;
		}
		
		int m_iPosition;
		int m_iWeight;
		int m_iParent;
	};

	int		FindPath(const PathFindingInput* i_pPathFindingInput);

	/*
	Starting from NodeToExplore search for a local min.
	-Found a single local min:
		- Add to solution ???
		- Explore him. Add its neighbour to NodeToExplore (update nodes already in but with a worst weight)
	-Found multiple sub optimal local min:
		- Explore all best sub-optimal. Add their neighbour to NodeToExplore, move sub-optimal in NodeExploredNotOptimal.
	*/
	void	ExplorationPhase(const PathFindingInput* i_pPathFindingInput);
	void	BackTrip();
	
	/*
	Before add a node in solution search sub-case:
	- Node come from a Node already in Solution(so optimum).
	- Node come from a Node in NodeExploredNotOptimal.
	*/
	void	AddToSolution(const PathFindingInput* i_pPathFindingInput, const Node& node);
	bool	IsTargetNode(const Node& node);

	//Fill the vector with the feasable four neighborhood
	void	GetNeighborhood(vector<int>& o_vNeighborhood, const int i_iIndexA, const int i_iMapWidth, int i_iMapHeight) const;
	void	GetNeighbourNodeFromVectorNode(const PathFindingInput* i_pPathFindingInput,vector<Node>& o_vOutput, const vector<Node>& i_vInput) const;
	void	GetLesserWeightNode(Node* o_oNode ,set<Node>* o_oSetToSearch);
	void	GetSubOptimalNodes(vector<Node>* o_vSubOptimal);

	void	ManageNewNode(const Node& node);
	void	MoveNodeToExplore(vector<Node>* i_vNodeToMove);
	
	bool	IsNodeInSolution(const Node& i_oNode) const;
	bool	IsNodeInNeighborhood(const PathFindingInput* i_pPathFindingInput,const Node& i_oNodeIn, const Node& i_oNodeNeighbour) const;

	void	Clear();

	PathFindingOutput		m_oPathFindingOutput;
	
	vector<Node>	m_vSolution;
	vector<Node>	m_vSolutionNotOptimus;
	set<Node>		m_vNodeToExplore;
	set<Node>		m_vNodeToExploreNotOptimal;
	Node			m_oTarget;

	int				m_iStepLimit;
	float			m_fStepLimitMultiplier = 2; //actually hardcoded (i prefer to avoid magic number) but can be an input variable =)
	int				m_iStepCounter;
	int				m_iTargetPosition;
	bool			m_bTargetFound;

	void			PrintNodeIn(const set<Node>* i_oSet) const;
	void			PrintNodeIn(const vector<Node>* i_oVec) const;

	int				m_iIterationCounter = 0; //Only for logging
};
