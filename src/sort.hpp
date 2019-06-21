#pragma once

namespace sort
{
	// internal fn
	template <typename T>
	size_t seek_min_max(T *a, const size_t size, bool (*pFn)(const void *, const void *), size_t start = 0)
	{
		size_t mIt = start;
		T m = a[mIt];
		for (size_t it = start; it < size; it++)
			if (!pFn(&m, &a[it])) {
				m = a[it];
				mIt = it;
			}
		return mIt;
	}

	template <typename T>
	void Bubble(T *a, const size_t size, bool (*pFn)(const void *, const void *))
	{
		for (size_t i = 0; i < size - 1; i++)
			for (size_t j = i + 1; j < size; j++)
				if (!pFn(&a[i], &a[j]))
					std::swap(a[i], a[j]);
	}

	template <typename T>
	void BubbleMod(T *a, const size_t size, bool (*pFn)(const void *, const void *))
	{
		bool sorted = true;
		for (size_t i = 0; i < size - 1; i++) {
			for (size_t j = i + 1; j < size; j++)
				if(!pFn(&a[i], &a[j]))
                    std::swap(a[i], a[j]);
                else
                    sorted = false;

			if (sorted)
				break;
		}
	}

	template <typename T>
	void Insertion(T *a, const size_t size, bool (*pFn)(const void *, const void *))
	{
		for (int i = 1; i < size; i++)
			for (int j = i; j > 0 && !pFn(&a[j - 1], &a[j]); j--)
				std::swap(a[j - 1], a[j]);
	}

	template <typename T>
	void Selection(T* a, const size_t size, bool (*pFn)(const void *, const void *))
	{
		size_t it = -1; //it's ok
		while (++it < size)
			std::swap(a[it], a[seek_min_max(a, size, pFn, it)]);
	}

	template <typename T>
	void Shell(T* a, const size_t size, bool (*pFn)(const void *, const void *))
	{
		T tmp;
		for (size_t step = size / 2; step > 0; step /= 2) {
			for (size_t j, i = step; i < size; i++) {
				tmp = a[i];
				for (j = i; j >= step; j -= step) {
					if (pFn(&tmp, &a[j - step]))
						a[j] = a[j - step];
					else
						break;
				}
				a[j] = tmp;
			}
		}
	}

	template <typename T>
	void QuickSort(T* a, const size_t size, bool(*pFn)(const void *, const void *), size_t first = 0)
	{
		size_t it = first, jt = size;
		T x = a[(it + jt) / 2];
		while (it <= jt)
		{
			while (a[it] > x)
				it++;
			while (a[jt] < x)
				jt--;

			if (it >= jt){
				std::swap(a[it], a[jt]);
				it++; jt--;
			}
		}
		if (first < jt)
			QuickSort(a, jt, pFn, first);
		if (size > it)
			QuickSort(a, size, pFn, it);
	}

	template <typename T>
	void QuickSort(T* a, const size_t size, bool(*pFn)(const void *, const void *))
	{
		QuickSort(a, size, pFn, 0);
	}

	template <typename T>
	void RadixSort(T* a, const size_t sz, bool(*pFn)(const void *, const void *))
	{
		T max = a[0];

		for (size_t it = 0; it < sz; it++) 
			if (a[it] > max)
				max = a[it];
		
		for (int n = 1; max / n > 0; n *= 10) {
			for (int i = 1; i < sz; i++)
				for (int j = i, a1 = (a[j - 1] / n) % 10, a2 = (a[j] / n) % 10; j > 0 && pFn(&a2, &a1); j--, a1 = (a[j - 1] / n) % 10, a2 = (a[j] / n) % 10)
					std::swap(a[j - 1], a[j]);
		}
	}

	// TODO
	template <typename T>
	void CountingSort(T* a, const size_t sz, bool(*pFn)(const void *, const void *))
	{
	}

	template <typename T>
	void DownwardMerge(T* a, const size_t start, const size_t end, bool(*pFn)(const void*, const void*))
	{
		auto Merge = [](T* a, const size_t start, const size_t c, const size_t end, bool(*pFn)(const void*, const void*))->void {
			int* b = new T[end *2];
			int i = start;
			int j = c + 1;
			for (int k = start; k <= end; k++) {
				if (j > end || (i <= c && pFn(&a[i], &a[j])))
					b[k] = a[i++];
				else 
					b[k] = a[j++];
			}
			
			for (int k = start; k <= end; k++) 
				a[k] = b[k];
		};

		if (end - start < 1)
			return;

		int c = (start + end) / 2;

		if (end - start > 1) {
			DownwardMerge(a, start, c, pFn);
			DownwardMerge(a, c + 1, end, pFn);
		}
		Merge(a, start, c, end, pFn);
	}

	template <typename T>
	void DownwardMerge(T* a, const size_t sz, bool(*pFn)(const void*, const void*))
	{
		DownwardMerge(a, 0, sz, pFn);
	}

	template <typename T>
	void GrowingMerge(T* a, const size_t sz, bool(*pFn)(const void*, const void*), size_t n = 1)
	{
		T* b = new T[sz];

		int c = 0;
		for (size_t i = 0; i < sz; i += 2 * n) {

			int it = 0, jt = 0;
			while ((it < n || jt < n) && c < sz) {
				if (!pFn(&a[i + it], &a[i + n + jt]) && jt < n && i + n + jt < sz)
					b[c++] = a[i + n + jt++];
				else if (it < n)
					b[c++] = a[i + it++];
				else
					b[c++] = a[i + n + jt++];
			}
		}
		if (sz % 2 && n <= sz / 2) 
			b[sz - 1] = a[sz - 1];
		
		for (int it = 0; it < sz; it++)
			a[it] = b[it];

		if (n > int(sz / 2.f + 0.5))
			return;

		GrowingMerge(a, sz, pFn, n * 2);
		delete[] b;
	}

	template <typename T>
	void GrowingMerge(T* a, const size_t sz, bool(*pFn)(const void*, const void*))
	{
		GrowingMerge(a, sz, pFn, 1);
	}

	// two-way merge
	template <typename T>
	void X2Merge(T* a, const size_t sz, bool(*pFn)(const void*, const void*), size_t n = 1)
	{
		int mid = sz / 2.f;
		if (n > mid)
			return;

		T* b = new T[sz];

		int c = 0, offset = mid;
		for (int i = 0; i <= offset; i += n) { //+ offset = mid
			if (i + offset == sz - 1 && sz % 2) { // !even sz
				b[sz - 1] = a[sz - 1];
				break;
			}
			else if (i == offset && !(sz % 2))
				break; //even

			int it = 0, jt = 0;
			while ((it < n || jt < n)) {
				if (!pFn(&a[i + it], &a[i + offset + jt]) && jt < n)
					b[c++] = a[i + offset + jt++];
				else if (it < n)
					b[c++] = a[i + it++];
				else
					b[c++] = a[i + offset + jt++];
			}
		}

		for (int it = 0; it < sz; it++)
			a[it] = b[it];

		X2Merge(a, sz, pFn, n * 2);
		delete[] b;
	}

	template <typename T>
	void X2Merge(T* a, const size_t sz, bool(*pFn)(const void*, const void*))
	{
		X2Merge(a, sz, pFn, 1);
	}
} // namespace sort