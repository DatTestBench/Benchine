#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		static T pInstance{};
		return &pInstance;
	}

	virtual ~Singleton() = default;
	DEL_ROF(Singleton);

protected:
	Singleton() = default;
};
