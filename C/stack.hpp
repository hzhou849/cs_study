class stack
{
	private:
		short *start;
		short *eq;
		short *dq;
		int capacity;
	
	public:
		Stack(int capacity); //constructor
		~Stack(); // deconstructor
		int push(short value);
		
};