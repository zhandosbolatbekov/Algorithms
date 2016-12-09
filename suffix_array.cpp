#include <bits/stdc++.h>

using namespace std;

const int N = 100500;

char s[N];
int n;
int suff[N], col[N];
int nsuff[N], ncol[N];
int head[N];
int cn = 0;

inline bool cmp(int i, int j) {
	return s[i] < s[j];
}

void suffix_array() {

	s[n++] = '#';

	for(int i = 0; i < n; ++i)
		suff[i] = i;

	sort(suff, suff + n, &cmp);

	for(int i = 0; i < n; ++i) {

		if(i == 0 || s[suff[i]] != s[suff[i-1]]) {
			head[cn] = i;
			col[suff[i]] = cn++;
		}
		else col[suff[i]] = cn - 1;
	}

	for(int len = 1; len <= n; len <<= 1) {

		for(int i = 0; i < n; ++i) {

			int pos = suff[i] - len;
			if(pos < 0) pos += n;
			nsuff[head[col[pos]]++] = pos;
		}

		for(int i = 0; i < n; ++i) 
			suff[i] = nsuff[i];
		cn = 0;

		for(int i = 0; i < n; ++i) {

			if(i == 0
				|| col[suff[i]] != col[suff[i-1]]
				|| col[(suff[i] + len) % n] != col[(suff[i-1] + len) % n]) {
				head[cn] = i;
				ncol[suff[i]] = cn++;
			}
			else ncol[suff[i]] = cn - 1;
		}

		for(int i = 0; i < n; ++i)
			col[i] = ncol[i];
	}

	n--;
	for(int i = 0; i < n; ++i)
		suff[i] = suff[i+1];
}

int p[N];
int lcp[N];

void calc_lcp() {

	int len = 0;

	for(int i = 0; i < n; ++i)
		p[suff[i]] = i;

	for(int i = 0; i < n; ++i) {

		int pos = p[i];
		if(pos == n - 1) {
			len = 0;
			lcp[pos] = 0;
			continue;
		}

		while(suff[pos] + len < n && suff[pos + 1] + len < n
				&& s[suff[pos] + len] == s[suff[pos+1] + len])
			len++;

		lcp[pos] = len;
		
		len--;
		if(len < 0) len = 0;
	}
}

int main() {

	scanf("%s", s);
	n = strlen(s);

	suffix_array();
	calc_lcp();

	for(int i = 0; i < n; ++i) {
		for(int j = suff[i]; j < n; ++j) 
			cout << s[j];
		cout << ": " << lcp[i] << endl;
	}

	return 0;
}