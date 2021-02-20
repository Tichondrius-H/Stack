#include<math.h>
#include"Stack.h"
#include<Windows.h>
#include<iomanip>
#include<string>
using namespace std;
struct Birth
{
	string year = " ";
	string month = " ";
	string day = " ";
};
struct Grade
{
	string Course;
	int score = 0;
	string credit;
	string type;
};
struct Student
{
	string id;
	string name;
	string sex;
	Birth birth;
	string major;
	string Class;
	Grade course[16];
	int coursenum = 0;
};
struct Course
{
	string name;
	string credit;
	string type;
	string id;
	int occu_volum = 0;
	int volum;
};
template <typename Key,typename Value>
struct AVL
{
	Key key;
	Value val;
	AVL* left, * right;
	int height;
	int size;
};
void Locate(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD   coordScreen = { short(x),short(y) };
	SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}
template <typename Key, typename Value>
void InitTree(AVL<Key, Value>*& bt, Key key, Value data)
{
	bt = new AVL<Key, Value>;
	bt->height = 1;
	bt->val = data;
	bt->key = key;
	bt->size = 1;
	bt->left = bt->right = NULL;
}
template <typename Key, typename Value>
int Height(AVL<Key, Value>*& bt)
{
	if (bt == NULL)
		return -1;
	else
		return bt->height;
}
template <typename Key, typename Value>
int Size(AVL<Key, Value>* bt) 
{

	if (bt == NULL)
		return 0;
	return bt->size;
}
template <typename Key, typename Value>
int BalanceFactor(AVL<Key, Value>*& bt)
{
	return Height(bt->left) - Height(bt->right);
}
template <typename Key, typename Value>
AVL<Key, Value>* L_Rotate(AVL<Key, Value>*& bt)
{
	AVL<Key, Value>* t = bt->right;
	bt->right = t->left;
	t->left = bt;
	bt->size = 1 + Size(bt->left) + Size(bt->right);
	bt->height = 1 + max(Height(bt->left), Height(bt->right));
	t->height = 1 + max(Height(t->left), Height(t->right));
	return t;
}
template <typename Key, typename Value>
AVL<Key, Value>* R_Rotate(AVL<Key, Value>*& bt)
{
	AVL<Key, Value>* t = bt->left;
	bt->left = t->right;
	t->right = bt;
	bt->size = 1 + Size(bt->left) + Size(bt->right);
	bt->height = 1 + max(Height(bt->left), Height(bt->right));
	t->height = 1 + max(Height(t->left), Height(t->right));
	return t;
}
template <typename Key, typename Value>
AVL<Key, Value>* Balance(AVL<Key, Value>*& bt)
{
	if (BalanceFactor(bt) < -1)
	{
		if (BalanceFactor(bt->right) > 0)
			bt->right = R_Rotate(bt->right);
		bt = L_Rotate(bt);
	}
	else if (BalanceFactor(bt) > 1)
	{
		if (BalanceFactor(bt->left) < 0)
			bt->left = L_Rotate(bt->left);
		bt = R_Rotate(bt);
	}
	return bt;
}
template <typename Key, typename Value>
void Insert(AVL<Key, Value>*& bt, Key key, Value data, bool exists = false)
{
	if (bt == NULL)
		InitTree(bt, key, data);
	if (bt->key > key)
		Insert(bt->left, key, data);
	else if (bt->key < key)
		Insert(bt->right, key, data);
	else
		bt->val = data;
	bt->size = 1 + Size(bt->left) + Size(bt->right);
	bt->height = 1 + max(Height(bt->left), Height(bt->right));
	bt = Balance(bt);
}
template <typename Key, typename Value>
AVL<Key, Value>* MinKey(AVL<Key, Value>*& bt)
{
	if (bt->left == NULL)
		return bt;
	return MinKey(bt->left);
}
template <typename Key, typename Value>
AVL<Key, Value>* DeleteMin(AVL<Key, Value>*& bt)
{
	if (bt->left == NULL)
		return bt->right;
	bt->left = DeleteMin(bt->left);
	bt->size = 1 + Size(bt->left) + Size(bt->right);
	bt->height = 1 + max(Height(bt->left), Height(bt->right));
	return Balance(bt);
}
template <typename Key, typename Value>
AVL<Key, Value>* KeyDelete(AVL<Key, Value>*& bt, Key key)
{
	if (bt == NULL)
		return NULL;
	if (bt->key > key)
		bt->left = KeyDelete(bt->left, key);
	else if (bt->key < key)
		bt->right = KeyDelete(bt->right, key);
	else
	{
		if (bt->left == NULL)
			return bt->right;
		else if (bt->right == NULL)
			return bt->left;
		else
		{
			AVL<Key, Value>* t = bt;
			bt = MinKey(t->right);
			bt->right = DeleteMin(t->right);
			bt->left = t->left;
		}
	}
	bt->size = 1 + Size(bt->left) + Size(bt->right);
	bt->height = 1 + max(Height(bt->left), Height(bt->right));
	return Balance(bt);
}
void BasicInfo()
{
	system("cls");
	Locate(40, 2); cout << "	     学生基本信息			 ";
	Locate(20, 3); cout << "===============================================================================";
	Locate(20, 4); cout << "	   学号		  姓名	   性别	    出生日期	" << setw(9) << "专业" << "	  班级";
	Locate(20, 5); cout << "===============================================================================";
}
void CourseInfo()
{
	system("cls");
	Locate(40, 2); cout << "	     现有课程信息			 ";
	Locate(20, 3); cout << "===============================================================================";
	Locate(20, 4); cout << "	   课程号	课程名称	  课程学分	课程类型	已选人数";
	Locate(20, 5); cout << "===============================================================================";
}
template <typename Key, typename Value>
void BasicPrint(AVL<Key, Value>*& bt, int yy)
{
	Locate(20, yy); cout << "   " << bt->key << "      " << setw(5) << bt->val.name << "	    " << bt->val.sex;
	cout << "	    " << bt->val.birth.year << "/" << bt->val.birth.month << "/" << bt->val.birth.day << "	";
	cout << setw(10) << bt->val.major << "	" << setw(8) << bt->val.Class;
	Locate(20, yy + 1); cout << "-------------------------------------------------------------------------------";
}
template <typename Key, typename Value>
int GradePrint(AVL<Key, Value>*& bt, int yy)
{
	if (yy == 2)
		system("cls");
	Locate(40, yy); cout << "	    学生个人成绩信息		" << endl; yy++;
	Locate(20, yy); cout << "==============================================================================="; yy++;
	Locate(20, yy); cout << "	    课程名称" << "	       " << "课程成绩" << "   	    " << "课程学分" << "   	    " << "课程类型"; yy++;
	Locate(20, yy); cout << "==============================================================================="; yy++;
	int n = 0, y = yy;
	for (; n < bt->val.coursenum; y = y + 2)
	{
		Locate(20, y); cout << "	     " << bt->val.course[n].Course << "		  " << bt->val.course[n].score << "		      " << bt->val.course[n].credit;
		cout << "	      " << bt->val.course[n].type;
		Locate(20, y + 1); cout << "-------------------------------------------------------------------------------";
		n++;
	}
	return y;
}
template <typename Key, typename Value>
void DispTree(AVL<Value, Key>*& bt)
{
	AVL<string, Student>* t = bt;
	SqStack<AVL<string, Student>>* st;
	InitStack(st);
	BasicInfo();
	short n = 6;
	while (st->count != 0 || t != NULL)
	{
		while (t != NULL)
		{
			Push(st, t);
			t = t->left;
		}
		if (st->count != 0)
		{
			Pop(st, t);
			BasicPrint(t, n);
			n = n + 2;
			t = t->right;
		}
	}
	Locate(20, n); cout << "输入0返回主界面：";
	DestroyStack(st);
}
template <typename Key, typename Value>
AVL<Key, Value>* KeySearch(AVL<Key, Value>*& bt, Key key)
{
	if (bt == NULL)
		return NULL;
	if (bt->key > key)
		return KeySearch(bt->left, key);
	else if (bt->key < key)
		return KeySearch(bt->right, key);
	else
		return bt;
}
template <typename Key, typename Value>
int NameSearch(AVL<Key, Value>*& bt, string name)
{
	AVL<string, Student>* t = bt;
	SqStack<AVL<string, Student>>* st;
	InitStack(st);
	short n = 6;
	BasicInfo();
	if (name.length() == 2)
	{
		while (st->count != 0 || t != NULL)
		{
			while (t != NULL)
			{
				Push(st, t);
				t = t->left;
			}
			if (st->count != 0)
			{
				Pop(st, t);
				if (t->val.name[0] == name[0])
				{
					BasicPrint(t, n);
					n = n + 2;
				}
				t = t->right;
			}
		}
	}
	else
	{
		while (st->count != 0 || t != NULL)
		{
			while (t != NULL)
			{
				Push(st, t);
				t = t->left;
			}
			if (st->count != 0)
			{
				Pop(st, t);
				if (t->val.name == name)
				{
					BasicPrint(t, n);
					n = n + 2;
				}
				t = t->right;
			}
		}
	}
	return n;
}
bool BetweenBirth(Birth bt,Birth* b1,Birth *b2)
{
	if (bt.year > b1->year && bt.year < b2->year)
		return true;
	else if (bt.year == b1->year || bt.year == b2->year)
	{
		if (bt.year < b2->year)
		{
			if (bt.month > b1->month)
				return true;
			else if (bt.month == b1->month)
			{
				if (bt.day >= b1->day)
					return true;
			}
		}
		else if (bt.year == b2->year)
		{
			if (bt.month < b2->month)
				return true;
			else if (bt.month == b2->month)
			{
				if (bt.day <= b2->day)
					return true;
			}
		}
	}
	return false;
}
bool ValidBirth(Birth* b)
{
	bool valid = false;
	bool lunar = false;
	string Lunar[] = { "02","04","06","09","11" };
	for (int i = 0; i < 5; i++)
	{
		if (b->month == Lunar[i])
		{
			lunar = true;
			break;
		}
	}
	if (lunar)
	{
		if (b->month != "02")
		{
			if (atoi(b->day.c_str()) > 0 && atoi(b->day.c_str()) <= 30)
				valid = true;
		}
		else
		{
			if ((atoi(b->year.c_str()) % 100 != 0 && atoi(b->year.c_str()) % 4 == 0) || (atoi(b->year.c_str()) % 400 == 0))
			{
				if (atoi(b->day.c_str()) > 0 && atoi(b->day.c_str()) <= 29)
					valid = true;
			}
			else
			{
				if (atoi(b->day.c_str()) > 0 && atoi(b->day.c_str()) <= 28)
					valid = true;
			}
		}
	}
	else
	{
		if (atoi(b->day.c_str()) > 0 && atoi(b->day.c_str()) <= 31)
			valid = true;
	}
	return valid;
}
template <typename Key, typename Value>
bool MatchCourse(AVL<Key,Value> * bt,string course)
{
	for (int i = 0; i < bt->val.coursenum; i++)
	{
		if (bt->val.course[i].Course == course)
			return true;
	}
	return false;
}
template <typename Key, typename Value>
int BirthSearch(AVL<Key, Value>*& bt, Birth* b1, Birth* b2)
{
	AVL<string, Student>* t = bt;
	SqStack<AVL<string, Student>>* st;
	InitStack(st);
	short n = 6;
	BasicInfo();
	while (st->count != 0 || t != NULL)
	{
		while (t != NULL)
		{
			Push(st, t);
			t = t->left;
		}
		if (st->count != 0)
		{
			Pop(st, t);
			if (BetweenBirth(t->val.birth, b1, b2))
			{
				BasicPrint(t, n);
				n = n + 2;
			}
			t = t->right;
		}
	}
	return n;
}
template <typename Key, typename Value>
int CourseSearch(AVL<Key, Value>*& bt, string course)
{
	AVL<string, Student>* t = bt;
	SqStack<AVL<string, Student>>* st;
	InitStack(st);
	short n = 6;
	BasicInfo();
	while (st->count != 0 || t != NULL)
	{
		while (t != NULL)
		{
			Push(st, t);
			t = t->left;
		}
		if (st->count != 0)
		{
			Pop(st, t);
			if (MatchCourse(t, course))
			{
				BasicPrint(t, n);
				n = n + 2;
			}
			t = t->right;
		}
	}
	return n;
}
template <typename Key, typename Value>
void CoursePrint(AVL<Key, Value>* bt, int yy)
{
	Locate(20, yy); cout << "	  " << bt->key << "	" << bt->val.name << "	    " << bt->val.credit << "	";
	cout << "	  " << bt->val.type << "		  " << bt->val.occu_volum << "/" << bt->val.volum;
	Locate(20, yy + 1); cout << "-------------------------------------------------------------------------------";
}
template <typename Key, typename Value>
void  CurrentCourse(AVL<Key, Value>*& bt)
{
	AVL<string, Course>* t = bt;
	SqStack<AVL<string, Course>>* st;
	InitStack(st);
	CourseInfo();
	short n = 6;
	while (st->count != 0 || t != NULL)
	{
		while (t != NULL)
		{
			Push(st, t);
			t = t->left;
		}
		if (st->count != 0)
		{
			Pop(st, t);
			CoursePrint(t, n);
			n = n + 2;
			t = t->right;
		}
	}
	Locate(20, n); cout << "输入0返回主界面：";
	DestroyStack(st);
}