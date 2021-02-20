template <typename T>
struct SqStack
{
	T* data[200];
	int count;
};
template <typename T>
void InitStack(SqStack<T>*& s)
{
	s = new SqStack<T>;
	s->count = 0;
}
template <typename T>
void DestroyStack(SqStack<T>*& s)
{
	delete s;
	s = NULL;
}
template <typename T>
bool Push(SqStack<T>*& s, T* e)
{
	if (s->count == 200)
		return false;
	s->data[s->count] = e;
	s->count++;
	return true;
}
template <typename T>
 bool Pop(SqStack<T>*& s, T*& e)
{
	if (s->count == 0)
		return false;
	e = s->data[s->count - 1];
	s->count--;
	return true;
}
template <typename T>
bool Peek(SqStack<T>*& s, T e)
{
	if (s->count == 0)
		return false;
	e = s->data[s->count - 1];
	return true;
}
