#include <iostream>
#include <stdexcept>

using namespace std;

template 
	<typename T>	//Assume Vector only takes in int or double

class Vector
{
	private:
		int sz;					//the number of elements in this Vector
		T * buf;				//the base of the array of Ts, you must allocate it
	
	public:
		Vector(int n)			//Vector v(10) -> create a 10 element Vector
		{
			sz = n;
			buf = new T[n];
			for (int index = 0; index < n; index++)
			{
				buf[index] = (T)0;
			}
		}
		Vector(initializer_list<T> L)	//Vector v1{T1, T2, T3};
		{
			sz = L.size();
			buf = new T[sz];

			typename initializer_list<T>::iterator it;
			int index = 0;
			for (it = L.begin(); it != L.end(); ++it)
			{
				buf[index++] = *it;
			}
		}
		~Vector()
		{
			delete [] buf;
		}
		Vector(const Vector & v)	//Vector v2(v1);
		{
			sz = v.sz;
			buf = new T[sz];
			for (int index = 0; index < v.sz; index++)
			{
				buf[index] = v.buf[index];
			}
		}
		int size() const
		{
			return sz;
		}
		T & operator[](const int i) 	//T x = V[i];
		{
			if (i < 0 || i > this->sz)
			{
				throw out_of_range("Error: Out-Of-Bounds index");
			}
			return buf[i];
		}
		//Access out-of-bound index should throw an error to be caught in outside scope
		T operator*(const Vector & v) const	//T x = V1 * V2
		{
			T sum = (T)0;
			int min = (this->sz < v.size()) ? this->sz : v.size();
			for (int index = 0; index < min; index++)
				sum += (this->buf[index] * v.buf[index]);

			return sum;
		}
				
		Vector operator+(const Vector & v)		//V3 = V1 + V2
		{
			int flag = 0;	//0 if *this has a smaller size than v, otherwise 1
			int min;
			if (this->sz < v.size())
				min = this->sz;
			else
			{
				min = v.size();
				flag = 1;
			}
			if (flag == 0)
			{
				//Vector *this has a smaller list
				Vector<T> answer(v.size());
				int index = 0;
				for ( ; index < min; index++)
				{
					answer.buf[index] = this->buf[index] + v.buf[index];
				}
				//Add the rest of the elements from the bigger list
				for ( ; index < v.size(); index++)
				{
					answer.buf[index] = v.buf[index];
				}
				answer.sz = v.size();
				return answer;
			}
			else
			{
				//Vector v has a smaller list
				Vector<T> answer(this->sz);
				int index = 0;
				for ( ; index < min; index++)
				{
					answer.buf[index] = this->buf[index] + v.buf[index];
				}
				//Add the rest of the elements from the bigger list
				for ( ; index < this->sz; index++)
				{
					answer.buf[index] = this->buf[index];
				}
				answer.sz = this->sz;
				return answer;
			}
		}
		//[1,2,3] + [4,5,6,7] = [5,7,9,7]
		const Vector & operator=(const Vector & v)	//V1 = V2
		{
			this->sz = v.sz;
			delete [] this->buf;
			this->buf = new T[v.sz];
			for (int index = 0; index < v.sz; index++)
			{
				this->buf[index] = v.buf[index];
			}
			return *this;
		}
		bool operator==(const Vector & v) const
		{
			bool answer = 1;
			if (this->sz != v.sz)
				answer = 0;				//They have different sizes

			if (answer)					//Must check the vector's list elements to check equivelance 
			{
				for (int index = 0; index < this->sz; index++)
				{
					if (this->buf[index] != v.buf[index])
					{
						answer = 0;
						return answer;
					}
				}
			}
			return answer;
		}
		bool operator!=(const Vector & v) const
		{
			bool result = 1;
			if (this->sz != v.sz)		//They have different sizes
				return result;

			for (int index = 0; index < v.sz; index++)
			{
				if (this->buf[index] != v.buf[index])
				{
					return result;
				}
			}
			//Same sizes and same elements so return false
			result = 0;
			return result;
		}
		friend Vector operator*(const int n, const Vector<T> & v)
		{
			Vector<T> answer(v.sz);
			for (int index = 0; index < v.sz; index++)
			{
				answer.buf[index] = n * v.buf[index];
			}
			return answer;
		}
		friend Vector operator+(const int n, const Vector<T> & v)
		{
			Vector<T> answer(v.sz);
			for (int index = 0; index < v.sz; index++)
			{
				answer.buf[index] = n + v.buf[index];
			}
			return answer;
		}
		//V1 = 20 + V2; --each element of V1 will be element of V2 + 20
		friend ostream& operator<<(ostream & out, const Vector<T> & v)
		{
			out << "(";
			for (int index = 0; index < v.sz; index++)
			{
				out << v.buf[index];
				if (index != (v.sz - 1))
					out << ",";
			}
			out << ")";
			return out;
		}
		//cout << V2; -- prints the vector in this format(v0, v1, v2,...);
};

int main()
{
	//Vector(T n);
	Vector<int> v1(2);
	v1[0] = 1;
	v1[1] = 2;

	Vector<double> v2(2);
	v2[0] = 1.4;
	v2[1] = 2.3;

	//Vector(T1, T2, T3};
	Vector<int> v3{4,5,6};
	Vector<double> v4{4.5, 5.5};

	//Vector(v1);
	Vector<int> v5(v1);
	Vector<double> v6(v2);

	//Vector.size()
	cout << "Checking Vector.size()..." << endl;
	cout << "Vector<double> v2{1.4,2.3} has size: " << v2.size() << endl;
	cout << "Vector<int> v3{4,5,6} has size: " << v3.size() << endl;
	cout << "\n";

	//Checking operator[]
	cout << "Checking operator []..." << endl;
	cout << "v2{1.4,2.3}" << endl;
	cout << "v3{4,5,6}" << endl;
	try
	{
		cout << "v3[1]: " << v3[1] << endl;
		cout << "v3[2]: " << v3[2] << endl;
		cout << "v2[0]: " << v2[0] << endl;
		cout << "v2[99]: " << v2[99] << endl;
	}
	catch(out_of_range & err)
	{
		cout << "v2[99] will yield an exception..." << endl;
		cerr << "IndexOutOfBoundsException" << endl;
	}
	cout << endl;

	//T operator*(const Vector & v);
	cout << "Checking operator*(const Vector & v)..." << endl;
	int sum = v1 * v3;
	double s1 = v4 * v4;
	cout << "v1{1,2} * v3{4,5,6}= " << sum << endl;
	cout << "v4{4.5,5.5} * v4{4.5,5.5}= " << s1 << endl;
	cout << "\n";
	
	//Vector operator+(...)
	cout << "Checking operator+(const Vector &v)..." << endl;
	Vector<double> v7 = v2 + v4;
	Vector<int> n1 = v3 + v3;
	Vector<double> u1{1.0,2.0};
	Vector<double> newThis = u1 + u1;
	cout << "v2{1.4,2.3} + v4{4.5,5.5} = " << "v7" << v7 << endl;	
	cout << "v3{4,5,6} + v3{4,5,6} = " << "n1" << n1 << endl;	
	cout << "u1{1.0,2.0} + u1{1.0,2.0} = " << "newThis" << newThis << endl;	
	cout << "\n";

	//Checking operator=(...)
	cout << "Checking operator=(const Vector &v)..." << endl;
	Vector<int> v8 = v3;
	Vector<double> n2 = v4;
	cout << "v8{} = v3{4,5,6} => " << "v8" << v8 << endl;
	cout << "n2{} = v4{4.5,5.5} => " << "n2" << n2 << endl;
	cout << "\n";
	
	//Checking operator==(...)
	cout << "Checking operator==(const Vector & v)..." << endl;
	bool result1 = (v3 == v8) ? true : false;
	bool r1 = (n2 == v2) ? true : false;
	cout << "v3{4,5,6} == v8{4,5,6} returns " << boolalpha << result1 << endl;
	cout << "n2{4.5,5.5} == v2{1.4,2.3} returns " << boolalpha << r1 << endl;
	cout << "\n";
	
	//Checking operator!=(...)
	cout << "Checking operator!=(const Vector & v)..." << endl;
	bool result2 = (v3 != v8) ? true : false;
	bool r2 = (n2 != v4) ? true : false;
	cout << "v3{4,5,6} != v8{4,5,6} returns " << boolalpha << result2 << endl;
	cout << "n2{4.5,5.5} != v4{4.5,5.5} returns " << boolalpha << r2 << endl;
	cout << "\n";
	
	//Checking operator*(...)
	cout << "Checking operator*(const int n, const Vector & v)..." << endl;
	Vector<double> v9 = 2 * v2;
	Vector<int> n3 = 20 * v1;
	cout << "v9 = 2 * v2{1.4,2.3} => " << "v9" << v9 << endl;
	cout << "n3 = 20 * v1{1,2} => " << "n3" << n3 << endl;
	cout << endl;
	
	//Checking operator+(...)
	cout << "Checking operator+(const int n, const Vector & v)..." << endl;
	Vector<int> v10 = 10 + v1;
	Vector<double> n4 = 35 + v2;
	cout << "v10 = 10 + v1{1,2} => " << "v10" << v10 << endl;
	cout << "n4 = 35 + v2{1.4,2.3} => " << "n4" << n4 << endl;
	cout << endl;
	
	//Checking operator<<(...)
	Vector<int> empty(4);
	cout << "Checking operator<<(ostream & out, const Vector & v)...: " << endl;
	cout << "v1" << v1 << endl;
	cout << "v2" << v2 << endl;
	cout << "empty" << empty << endl;
	cout << endl;
	
}
