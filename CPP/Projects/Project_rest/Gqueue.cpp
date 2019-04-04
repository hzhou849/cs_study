/* Generic Queue class 
 *
 * template <typename T1, typename T2>
 * struct My_pair
 * 	T1 first;
 *  T2 second;
 */


#include <iostream>

template <typename T>
class Gqueue {
private:
	short *start;
	T	  *value;	// passing pointer to the object not copying
	short *eq;
	short *dq;
	int bufferSize;
public:
	Gqueue(int b);
	~Gqueue();
	void init2();
};

template <typename T>
Gqueue<T>::Gqueue(int b) :start{nullptr},value{nullptr}, eq{nullptr}, dq{nullptr}, bufferSize{0} {
	this->start = new T[b];
	this->eq = start;
	this->dq = this->start;
	this->bufferSize = b;

}
template <typename T>
Gqueue<T>::~Gqueue() {
	// de-allocate heap queue
	delete[] start;
}
template <typename T>
void Gqueue<T>::init2() {
	std::cout << " init" << std::endl;
}


int main() {
	Gqueue gq(5);
	

}



