#ifndef _MONEY_H
#define _MONEY_H

class Money {
	int MONEY = 1000;		//�ؿ��ڵ�ǰǮ������ʼֵ1000
public:
	int getcrntMoney() {
		return MONEY;
	}
	void changeMoney(int num) {
		MONEY += num;
	}
};

#endif // !_MONEY_H

