class stack
{
	private:
		short *start;
		short *eq;
		short *dq;
		int capacity;
	
	public:
		void Push(short value);
		Stack(int capacity); //constructor
		~Stack(); // deconstructor
};