#pragma once
#include "multitree.h"
/*************************************������****************************************/
//������,���ݴ������Ĳ���,ѡ�����ĳ������
using namespace SmartDongLib ;
class Context 
{
private:
	MultiTree *strategyChild;
public:
	Context(MultiTree *child)
 	{
		strategyChild=child;
	}

	void Insert(int target)
 	{
		strategyChild->insert(target);
	}
	void LevelDisplay()
	{
		strategyChild->level_display();
	};
	
	void Del(int target)
	{
		strategyChild->del(target);
	};
	
	void Inorder_Print()
	{
		strategyChild->inorder_print();
	};
	
	// tree node num
	void NodeNum_Print()
	{
		strategyChild->NodeNum_print();
	};
};
