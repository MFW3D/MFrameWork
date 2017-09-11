#pragma once
#include <mutex>
#include <memory>

namespace MFW {
	template <class T>
	class Singleton
	{
	protected:
		Singleton() {};
	private:
		Singleton(const Singleton&) {};
		Singleton& operator=(const Singleton&) {};
		static std::shared_ptr<T> m_instance;
		static std::mutex mutex;
	public:
		static std::shared_ptr<T> GetInstance();
	};

	template <class T>
	std::shared_ptr<T> Singleton<T>::GetInstance()
	{
		std::lock_guard<std::mutex> lg(mutex);
		if (m_instance == nullptr)
		{
			m_instance = std::shared_ptr<T>(new T());
		}
		return m_instance;
	}


	template <class T>
	std::mutex Singleton<T>::mutex;

	template <class T>
	std::shared_ptr<T> Singleton<T>::m_instance = nullptr;
}