#pragma once

namespace PathFindingStructs
{
	struct PathFindingInput
	{
		//Start position
		int iStartX = -1;
		int iStartY = -1;

		//Target Position
		int iTargetX = -1;
		int iTargetY = -1;

		//Topology
		unsigned char* pMap = nullptr;
		//GridSize
		int iMapWidth = -1;
		int iMapHeight = -1;

		//Max solution deep
		int	iOutBufferSize = -1;

		PathFindingInput& operator=(const PathFindingInput* const i_pPathFindingInput)
		{
			this->Clear();
			this->iStartX = i_pPathFindingInput->iStartX;
			this->iStartY = i_pPathFindingInput->iStartY;
			this->iTargetX = i_pPathFindingInput->iTargetX;
			this->iTargetY = i_pPathFindingInput->iTargetY;
			memcpy(&this->pMap, &i_pPathFindingInput->pMap, sizeof(i_pPathFindingInput->pMap));
			this->iMapWidth = i_pPathFindingInput->iMapWidth;
			this->iMapHeight = i_pPathFindingInput->iMapHeight;
			this->iOutBufferSize = i_pPathFindingInput->iOutBufferSize;
			return *this;
		}

		void Clear()
		{
			iStartX = -1;
			iStartY = -1;
			iTargetX = -1;
			iTargetY = -1;
			pMap = nullptr;
			iMapWidth = -1;
			iMapHeight = -1;
			iOutBufferSize = -1;
		}
	};

	struct PathFindingOutput
	{

		~PathFindingOutput()
		{
			delete[] m_pOutBuffer;
		}

		//Cell's index defining path
		int		m_iSize;

		void Clear()
		{
			m_iSize = -1;
			delete[] m_pOutBuffer;
			m_pOutBuffer = nullptr;
		}

		void AllocArray(size_t iSize)
		{
			if (m_pOutBuffer != nullptr)
			{
				delete[] m_pOutBuffer;
				m_pOutBuffer = nullptr;
			}
			
			m_pOutBuffer = new int[iSize];
		}

		int* At(int index)
		{
			return &m_pOutBuffer[index];
		}
		int* At(int index) const
		{
			return &m_pOutBuffer[index];
		}

	private:
		int*	m_pOutBuffer;
		
	};
}