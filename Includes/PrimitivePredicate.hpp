#ifndef COMPARATOR_HPP
	#define COMPARATOR_HPP
#include <string>
	class StringPredicate
	{
		private:
			std::string target;
		public:
			explicit StringPredicate(const std::string& v);
			bool operator () (const std::string& a);
			bool operator == (const std::string& a);
	};
	class SizeTPredicate
	{
		private:
			size_t target;
		public:
			explicit SizeTPredicate(size_t v);
			bool operator () (size_t a);
			bool operator == (size_t a);
	};
#endif
