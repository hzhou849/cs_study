/* C++ STL Queues
 *
 * FIFO
 * std::queue
 * #include <queue>
 * 
 * push			-insert element at back of queue
 * pop			- remove element form the front of the queue
 * 
 * front		- access element at the fron
 * back			-access element at the back
 * 
 * empty		- bool isEmpty?
 * size			- return the number of e in the queue
 * 
 * 
 * //since there is no underlying info about the underlying container,
 *  so STL will use a deque by default 
 *  std::queue<int> q; 
 * 
 * std::queue<int, std::list<int>> q2;			// list
 * std::queue<int, std::deque<int>>q3;			//deque
 */ 

// Function to dump the queue.
template<typename T>
void display(std::queue <T> q) {
	std::cout << "{";
	while (!q.empty()) {
		T.elem = q.front();
		q.pop();
		std::cout << elem << "";

	}
	std::cout << "}" std::endl;
}