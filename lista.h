#pragma once

#pragma once

template <typename T>
class lista {
	struct wezel {
		T ww;
		wezel* nastepca;
		wezel() : nastepca(NULL), ww(NULL) {}
		wezel(T wartosc) : nastepca(NULL) {
			this->ww = wartosc;
		};
		wezel(T wartosc, wezel* nastepca) : nastepca(nastepca) {
			this->nastepca = nastepca;
			this->ww = wartosc;
		};
	};
	wezel* pierwszyW;
	wezel* ostatniW;
	int wielkosc;

	class iterator {


	public:
		wezel* wskaznik;
		friend class list;

		iterator() : wskaznik(nullptr) {

		}
		iterator(wezel* wskaznik) : wskaznik(wskaznik) {
		}
		iterator& operator++() {
			wskaznik = wskaznik->nastepca;
			return *this;
		}
		iterator operator++(int) {
			iterator pomoc = *this;
			wskaznik = wskaznik->nastepca;
			return pomoc;
		}
		T& operator*() {
			return wskaznik->ww;
		}
		wezel* operator->() {
			return wskaznik;
		}
		bool operator!=(iterator i) {
			return wskaznik != i.wskaznik;
		}
		bool operator==(iterator i) {
			return wskaznik == i.wskaznik;
		}

	};

	class constiterator {


	public:
		const wezel* wskaznik;
		friend class list;
		constiterator() : wskaznik(pierwszyW) {
		}
		constiterator& operator++() {
			wskaznik = wskaznik->nastepca;
			return *this;
		}
		constiterator operator++(int) {
			constiterator pomoc = *this;
			wskaznik = wskaznik->nastepca;
			return pomoc;
		}
		const T& operator*() {
			wskaznik->ww;
		}
		wezel* operator->() {
			return wskaznik;
		}
		bool operator!=(iterator i) {
			return wskaznik != i->wskaznik;
		}
		bool operator<(iterator i) {
			return wskaznik < i->wskaznik;
		}

	};
public:
	lista() {
		pierwszyW = ostatniW = NULL;
	}
	lista(int ilosc, const std::function<T(const size_t)>& wartosc) {
		wielkosc = ilosc;
		wezel* el = new wezel(wartosc(0));
		pierwszyW = el;
		ostatniW = pierwszyW;
		for (int i = 1; i < ilosc; i++) {
			el->nastepca = new wezel(wartosc(i));
			el = el->nastepca;
			ostatniW = el;
		}
	}
	~lista() {
		wezel* el = pierwszyW;
		while (el->nastepca != nullptr) {
			pierwszyW = el->nastepca;
			delete el;
			el = pierwszyW;
		}
	}
	iterator begin() {
		return iterator(pierwszyW);
	}
	iterator end() {
		return iterator(ostatniW->nastepca);
	}
	int size() {
		return wielkosc;
	}
	void push_back(T wartosc) {
		wezel* el = pierwszyW;
		while (true) {
			if (el->nastepca == nullptr) {
				el->nastepca = new wezel(wartosc);
				ostatniW = el->nastepca;
				return;
			}
			else {
				el = el->nastepca;
			}
		}
	}
	void insert(iterator i, T wartosc) {
		if (i == this->begin()) {
			pierwszyW = new wezel(wartosc, pierwszyW);
			return;
		}
		if (i == this->end()) {
			push_back(wartosc);
			return;
		}
		wezel* el = pierwszyW->nastepca;
		wezel* elp = pierwszyW;
		while (el != i.wskaznik) {
			elp = el;
			el++;
		}
		wezel* eln = new wezel(wartosc, el);
		elp->nastepca = eln;
	}
	void erase(iterator i) {
		wezel* el = pierwszyW;
		wezel* elp = nullptr;

		if (i == this->begin()) {
			i.wskaznik = pierwszyW->nastepca;
			delete pierwszyW;
			pierwszyW = i.wskaznik;
			return;
		}

		do {
			if (el->nastepca == nullptr) {
				elp->nastepca = nullptr;
				ostatniW = elp;
				delete el;
				return;
			}
			elp = el;
			el = el->nastepca;
		} while (el != i.wskaznik);
		elp->nastepca = el->nastepca;
		delete el;
	}
};