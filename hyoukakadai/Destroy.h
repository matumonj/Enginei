#pragma once

template <class T>
inline void Destroy(T*& p) {
	delete p;
	p = nullptr;
}