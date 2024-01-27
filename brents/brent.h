#include <vector>

using std::vector;


class Brent {
public:
class entry {
	public:
		bool valid;
		int data;

		entry() {
			valid = false;
		}
};
	vector<entry> data_vec;

public:
	Brent(int);
    int hash(int) const;
    int hash2(int) const;
	void insert(int);
	vector<int> calculateLQ(int, int);
	int find_num_probes(int) const;
	double find_average_num_probes() const;

};