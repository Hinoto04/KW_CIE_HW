
#include <iostream>
#include <string>
using namespace std;

int power(int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

class Term {
private:
	int m_Coefficient;
	int m_Exponent;
	Term* m_pNext;
public:
	Term() {
		this->m_Coefficient = 0;
		this->m_Exponent = 0;
		this->m_pNext = NULL;
	}
	~Term() { return; }
	void setNext(Term* t) { m_pNext = t; }
	void insert(Term* t) {
		if (m_pNext) {
			t->setNext(m_pNext);
			m_pNext = t;
			return;
		}
		m_pNext = t;
	}
	Term* getNext() { return this->m_pNext; }
	int getCoefficient() { return this->m_Coefficient; }
	int getExponent() { return this->m_Exponent; }
	void setCoefficient(int coef) { this->m_Coefficient = coef; }
	void setExponent(int expo) { this->m_Exponent = expo; }
	string str() {
		string s;
		if (this->m_Exponent > 0) {
			if (this->m_Coefficient != 1) {
				s = to_string(this->m_Coefficient);
			}
			else {
				s = string("");
			}
			s += string("x^") + to_string(this->m_Exponent);
		}
		else {
			s = to_string(this->m_Coefficient);
		}
		return s;
	}
};

class Polynomial {
private:
	Term* m_pHead;
public:
	Polynomial() {
		this->m_pHead = NULL;
	}
	~Polynomial() {
		return;
		for (Term* cur = this->m_pHead; this->m_pHead; cur = this->m_pHead) {
			this->m_pHead = this->m_pHead->getNext();
			delete cur;
		}
	}

	void addTerm(int coeff, int exp) {
		Term* newNode = new Term();
		newNode->setCoefficient(coeff);
		newNode->setExponent(exp);

		Term* cur = this->m_pHead;
		cur = this->m_pHead;
		if (cur == NULL) {
			this->m_pHead = newNode;
			//cout << "빈 다항식에 등록" << endl;
			return;
		}
		if (cur->getExponent() == exp) {
			//차수가 같은 항이 있고, 계수를 더하여도 0이 되지 않는 경우
			if (cur->getCoefficient() + coeff) {
				cur->setCoefficient(cur->getCoefficient() + coeff);
				//cout << "동차항 발견!" << endl;
				return;
			}
			//차수가 같은 항이 있고, 계수를 더하면 0이 되는 경우
			this->m_pHead = cur->getNext();
			delete cur;
			return;
		}
		if (cur->getExponent() < exp) {
			newNode->setNext(cur);
			this->m_pHead = newNode;
			//cout << "가장 큰 차수의 항이 등록됨" << endl;
			return;
		}
		while (cur->getNext() != NULL) {
			if (cur->getNext()->getExponent() == exp) {
				//차수가 같은 항이 있고, 계수를 더하여도 0이 되지 않는 경우
				if (cur->getNext()->getCoefficient() + coeff) {
					cur->getNext()->setCoefficient(cur->getNext()->getCoefficient() + coeff);
					//cout << "동차항 발견!" << endl;
					return;
				}
				//차수가 같은 항이 있고, 계수를 더하면 0이 되는 경우
				Term* temp = cur->getNext();
				cur->setNext(temp->getNext());
				delete temp;
				return;
			}
			if (cur->getNext()->getExponent() < exp && cur->getExponent() > exp) {
				//cout << "중간에 삽입" << endl;
				cur->insert(newNode);
				return;
			}
			cur = cur->getNext();
		}
		//cout << "가장 마지막 항에 등록" << endl;
		cur->setNext(newNode);
		return;
	}
	void printPolynomial() {
		Term* cur = this->m_pHead;
		if (cur != NULL) {
			cout << cur->str();
			cur = cur->getNext();
		}
		while (cur != NULL) {
			cout << " + " << cur->str();
			cur = cur->getNext();
		}
		cout << endl;
	}
	Polynomial operator+(const Polynomial& poly) {
		Polynomial result;
		Term* cur = this->m_pHead;
		while (cur != NULL) {
			result.addTerm(cur->getCoefficient(), cur->getExponent());
			cur = cur->getNext();
		}
		cur = poly.m_pHead;
		while (cur != NULL) {
			result.addTerm(cur->getCoefficient(), cur->getExponent());
			cur = cur->getNext();
		}
		return result;
	}
	Polynomial operator-(const Polynomial& poly) {
		Polynomial result;
		Term* cur = this->m_pHead;
		while (cur != NULL) {
			result.addTerm(cur->getCoefficient(), cur->getExponent());
			cur = cur->getNext();
		}
		cur = poly.m_pHead;
		while (cur != NULL) {
			result.addTerm(-1*cur->getCoefficient(), cur->getExponent());
			cur = cur->getNext();
		}
		return result;
	}
	Polynomial differentiation() {
		Polynomial result;
		Term* cur = this->m_pHead;
		while (cur != NULL) {
			result.addTerm(cur->getCoefficient()*cur->getExponent(), cur->getExponent() - 1);
			if (cur->getExponent() == 1) {
				delete cur->getNext();
				cur->setNext(NULL);
			}
			cur = cur->getNext();
		}
		return result;
	}
	int calculate(int x) {
		int result = 0;
		Term* cur = this->m_pHead;
		while (cur != NULL) {
			result += cur->getCoefficient() * power(x, cur->getExponent());
			cur = cur->getNext();
		}
		return result;
	}
};

int main()
{
	Polynomial poly;
	//항 추가 및 삭제 제대로 확인
	poly.addTerm(3, 3); //3x^3
	poly.addTerm(3, 4); //3x^4
	poly.addTerm(1, 1); //1x^1
	poly.addTerm(2, 2); //2x^2
	poly.addTerm(2, 3); //2x^3 -> 3x^3에 더해짐
	poly.addTerm(-2, 2); //-2x^2 -> 2x^2와 더해져 0이 되어 삭제 (중간항)
	poly.addTerm(-1, 1); //-1x^1 -> 1x^1과 더해져 0이 되어 삭제 (끝항)
	poly.addTerm(-3, 4); //-3x^4 -> 3x^4와 더해져 0이 되어 삭제 (head)

	poly.addTerm(2, 5);
	poly.addTerm(6, 0);
	poly.addTerm(3, 4);

	cout << "Polynomial 1 : ";
	poly.printPolynomial();

	Polynomial poly2;
	poly2.addTerm(-3, 3);
	poly2.addTerm(1, 2);
	poly2.addTerm(6, 1);
	poly2.addTerm(4, 0);

	cout << "Polynomial 2 : ";
	poly2.printPolynomial();

	cout << "Poly2 Calculate X = 2 : ";
	cout << poly2.calculate(2) << endl;

	Polynomial poly3;
	poly3 = poly - poly2;
	cout << "Polynomial Result : ";
	poly3.printPolynomial();
	poly3 = poly3.differentiation();

	cout << "Differential Result : ";
	poly3.printPolynomial();

	return 0;
}
