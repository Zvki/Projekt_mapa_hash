#pragma once
template < class K, class W>

class map {
private:


	struct dane {
		K klucz;
		W wartosc;
	};

	dane** key_value;
	size_t size_row = 10;
	size_t size_col;


public:

	class iterator {

	private:

		size_t row_index;
		size_t col_index;
		map<K, W>* map_ptr;

	public:

		friend class map;

		iterator(size_t col_index, size_t row_index, map<K, W>* map_ptr) : col_index(col_index), row_index(row_index), map_ptr(map_ptr) {

		}

		iterator operator++() {
			row_index++;
			while (col_index < map_ptr->size_col && row_index < map_ptr->size_row) {
				if (map_ptr->key_value[col_index][row_index].klucz != 0 || map_ptr->key_value[col_index][row_index].wartosc != 0) {
					return *this;
				}
				row_index++;
			}

			col_index++;
			row_index = 0;

			while (col_index < map_ptr->size_col && map_ptr->key_value[col_index][row_index].klucz == 0 && map_ptr->key_value[col_index][row_index].wartosc == 0) {
				col_index++;
			}

			return *this;

		}

		dane& operator*() const {
			return map_ptr->key_value[col_index][row_index];
		}

		dane* operator->() const {
			return &(map_ptr->key_value[col_index][row_index]);
		}

		bool operator!=(const iterator& other) const {
			return col_index != other.col_index || row_index != other.row_index;
		}

	};

	class constiterator {

	private:

		size_t row_index;
		size_t col_index;
		map<K, W>* map_ptr;

	public:

		friend class map;

		constiterator(size_t col_index, size_t row_index, map<K, W>* map_ptr) : col_index(col_index), row_index(row_index), map_ptr(map_ptr) {

		}

		const iterator operator++() {
			row_index++;
			while (col_index < map_ptr->size_col && row_index < map_ptr->size_row) {
				if (map_ptr->key_value[col_index][row_index].klucz != 0 || map_ptr->key_value[col_index][row_index].wartosc != 0) {
					return *this;
				}
				row_index++;
			}

			col_index++;
			row_index = 0;

			while (col_index < map_ptr->size_col && map_ptr->key_value[col_index][row_index].klucz == 0 && map_ptr->key_value[col_index][row_index].wartosc == 0) {
				col_index++;
			}

			return *this;

		}

		const dane& operator*() const {
			return map_ptr->key_value[col_index][row_index];
		}

		const dane* operator->() const {
			return &(map_ptr->key_value[col_index][row_index]);
		}

		const bool operator!=(const iterator& other) const {
			return col_index != other.col_index || row_index != other.row_index;
		}

	};

	map(size_t size_col1) : size_col(size_col1) {
		key_value = new dane* [size_col1];
		for (size_t i = 0; i < size_col1; i++) {
			key_value[i] = new dane[size_row];
		}
		set_null(key_value);
	}

	~map() {
		for (int i = 0; i < size_col; i++) {
				delete key_value[i];
		}
	}

	void set_null(dane** mapa) {
		for (int i = 0; i < size_col; i++) {
			for (int j = 0; j < size_row; j++) {
				mapa[i][j].klucz = 0;
				mapa[i][j].wartosc = 0;
			}
		}
	}

	auto hash(K klucz) -> size_t {
		if (klucz == 0) {
			return klucz + 1;
		}
		else {
			if (typeid(K) == typeid(char*)) {
				size_t suma = 0;
				for (size_t l = 0; l < klucz; l++) {
					suma += (size_t)l;
				}
				return suma % size_col;
			}
			else {
				size_t klucz1 = klucz % size_col;
				if (klucz1 == 0) {
					return klucz1 + 1;
				}
				else {
					return klucz1;
				}
			}
		}
		
	}

	void memoryl(size_t pozycja) {
		if (pozycja >= size_row) {
			dane_resize_row();
		}
		else
		{
			return;
		}
	}

	void dane_resize_row() {
		size_t size_row_h = size_row;
		dane** key_value_h = new dane*[size_col];
		for (size_t i = 0; i < size_col; i++) {
			key_value_h[i] = new dane[size_row];
		}
		set_null(key_value_h);
		for (size_t l = 0; l < size_col; l++) {
			for (size_t k = 0; k < size_row; k++) {
				key_value_h[l][k] = key_value[l][k];
			}
		}
		size_row = 2 * size_row;
		for (size_t i = 0; i < size_col; i++) {
			key_value[i] = new dane[size_row];
		}
		set_null(key_value);
		for (size_t l = 0; l < size_col; l++) {
			for (size_t k = 0; k < size_row_h; k++) {
				key_value[l][k] = key_value_h[l][k];
			}
			delete key_value_h[l];
		}
	}



	void dane_insert(K key, W value, size_t i, size_t pozycja) {
		key_value[i][pozycja].klucz = key;
		key_value[i][pozycja].wartosc = value;
	}


	void insert(K key, W value) {
		bool set = true;
		bool ml = true;
		size_t pozycja = 0;
		size_t hashi = hash(key);
		for (size_t i = 0; i < size_col; i++) {
			if (hashi== i) {
				while (set) {
					if (key_value[i][pozycja].klucz == 0 && key_value[i][pozycja].wartosc != 0) {
						pozycja++;
					}
					if(key_value[i][pozycja].klucz != 0 && key_value[i][pozycja].wartosc != 0) {
						pozycja++;
					}
					else {
						memoryl(pozycja);
						set = false;
						dane_insert(key, value, i, pozycja);
					}
				}
			}
		}
	}

	W get(K key) {
		size_t hashi = hash(key);
		for (size_t l = 0; l < size_col; l++) {
			if (l == hashi) {
				for (size_t k = 0; k < size_row; k++) {
					if (key == key_value[l][k].klucz) {
						return key_value[l][k].wartosc;
					}
				}
			}
			
		}
		throw std::out_of_range(" ");
	}

	W operator[](K key) {
		try {
			return get(key);
		}
		catch (const std::out_of_range& e) {
			std::cerr << "Nie ma takiego elementu" << e.what() << std::endl;
		}
	}
	

	iterator begin() {
		return iterator(0, 0, this);
	}

	iterator end() {
		return iterator(size_col, 0, this);
	}
};
