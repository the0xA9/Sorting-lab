#pragma once

namespace sort
{
	template <typename T>
	size_t seek_min_max(T *a, const size_t size, bool (*pFn)(void *, void *), size_t start = 0)
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
	void Bubble(T *a, const size_t size, bool (*pFn)(void *, void *))
	{
		for (size_t i = 0; i < size - 1; i++)
			for (size_t j = i + 1; j < size; j++)
				if (!pFn(&a[i], &a[j]))
					std::swap(a[i], a[j]);
	}

	template <typename T>
	void BubbleMod(T *a, const size_t size, bool (*pFn)(void *, void *))
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
	void Insertion(T *a, const size_t size, bool (*pFn)(void *, void *))
	{
		for (int i = 1; i < size; i++)
			for (int j = i; j > 0 && !pFn(&a[j - 1], &a[j]); j--)
				std::swap(a[j - 1], a[j]);
	}

	template <typename T>
	void Selection(T *a, const size_t size, bool (*pFn)(void *, void *))
	{
		size_t it = -1; //it's ok
		while (++it < size)
			std::swap(a[it], a[seek_min_max(a, size, pFn, it)]);
	}

	template <typename T>
	void Shell(T *a, const size_t size, bool (*pFn)(void *, void *))
	{
		int j;
		float tmp;
		for (int step = size / 2; step > 0; step /= 2) {
			for (int i = step; i < size; i++) {
				tmp = a[i];
				for (j = i; j >= step; j -= step) {
					if (tmp < a[j - step])
						a[j] = a[j - step];
					else
						break;
				}
				a[j] = tmp;
			}
		}
	}
} // namespace sort