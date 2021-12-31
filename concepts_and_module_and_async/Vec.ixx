export module math.Vec;
import <iostream>;
import <type_traits>;
import math.Utils;
export namespace math {
	enum print_option {
		having_inner_and_is_inner = 0,
		having_inner_but_not_inner = 1,
		is_inner_not_having_inner = 2,
		not_inner_and_not_having_inner = 3
	};
	template<typename Vec>
	using Scalar = std::decay<decltype(Vec()[0])>::type;
	template<typename vec_value>
	concept inner_type_accept = (std::floating_point<vec_value> ||
		std::floating_point<Scalar<vec_value>>) &&
		requires (std::ostream & out, const vec_value & v) {
		out << v;
	};
	template<inner_type_accept vec_value, const int len, const print_option is_inner>
	class BasicVec {
	public:
		BasicVec();
		BasicVec(vec_value fill);
		BasicVec(vec_value values[len]);
		inline BasicVec<vec_value, len, is_inner> operator+(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner>& operator+=(const BasicVec<vec_value, len, is_inner>& rhs);
		inline BasicVec<vec_value, len, is_inner> operator-(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner>& operator-=(const BasicVec<vec_value, len, is_inner>& rhs);
		inline vec_value operator*(const BasicVec<vec_value, len, is_inner>& rhs) const;
		inline BasicVec<vec_value, len, is_inner> operator*(const vec_value& rhs) const;
		inline BasicVec<vec_value, len, is_inner>& operator*=(const vec_value& rhs);
		inline BasicVec<vec_value, len, is_inner> operator/(const vec_value& rhs) const;
		inline BasicVec<vec_value, len, is_inner>& operator/=(const vec_value& rhs);
		inline BasicVec<vec_value, 3, is_inner> cross(BasicVec<vec_value, 3, is_inner>& rhs) const;
		inline virtual double length_squared() const final;
		inline virtual double length() const final;
		inline virtual BasicVec<vec_value, len, is_inner> unit_vec() const final;
		auto operator[](int i) const->vec_value;
		auto operator[](int i)->vec_value&;
	protected:
		vec_value inner[len];
	};
	template<inner_type_accept vec_value, const int len, const print_option is_inner>
	inline std::ostream& operator<<(std::ostream& out, const BasicVec<vec_value, len, is_inner>& rhs)
	{
		out << "[";
		for (int i = 0; i < len; i++) {
			out << rhs[i];
			if (i != len - 1) {
				out << ",";
				switch (is_inner) {
				case not_inner_and_not_having_inner:
					break;
				case is_inner_not_having_inner:
					break;
				default:
					out << "\n";
				}
			}
			else {
				out << "]";
			}
		}
		return out;
	}
	template<const int len>
	using Vec = BasicVec<double, len, not_inner_and_not_having_inner>;
	using Vec3 = Vec<3>;
};
using namespace math;

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec()
{
}

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec(vec_value fill)
{
	for (int i = 0; i < len; i++) {
		inner[i] = fill;
	}
}

template<inner_type_accept vec_value, int len, print_option is_inner>
BasicVec<vec_value, len, is_inner>::BasicVec(vec_value values[len])
{
	for (int i = 0; i < len; i++) {
		this->inner[i] = values[i];
	}
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator+(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] + rhs[i];
	}
	return res;
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner>& math::BasicVec<vec_value, len, is_inner>::operator+=(const BasicVec<vec_value, len, is_inner>& rhs)
{
	for (int i = 0; i < len; i++) {
		this->inner[i] += rhs[i];
	}
	return *this;
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator-(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] - rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner>& math::BasicVec<vec_value, len, is_inner>::operator-=(const BasicVec<vec_value, len, is_inner>& rhs)
{
	for (int i = 0; i < len; i++) {
		this->inner[i] -= rhs[i];
	}
	return *this;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline vec_value BasicVec<vec_value, len, is_inner>::operator*(const BasicVec<vec_value, len, is_inner>& rhs) const
{
	vec_value res = vec_value{};
	for (int i = 0; i < len; i++) {
		res += this->inner[i] * rhs[i];
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> math::BasicVec<vec_value, len, is_inner>::operator*(const vec_value& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++){
		res[i] = this->inner[i] * rhs;
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner>& math::BasicVec<vec_value, len, is_inner>::operator*=(const vec_value& rhs)
{
	for (int i = 0; i < len; i++) {
		this->inner[i] *= rhs;
	}
	return *this;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> BasicVec<vec_value, len, is_inner>::operator/(const vec_value& rhs) const
{
	auto res = BasicVec<vec_value, len, is_inner>();
	for (int i = 0; i < len; i++) {
		res[i] = this->inner[i] / rhs;
	}
	return res;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner>& math::BasicVec<vec_value, len, is_inner>::operator/=(const vec_value& rhs)
{
	for (int i = 0; i < len; i++) {
		this->inner[i] /= rhs;
	}
	return *this;
}
template<inner_type_accept vec_value, int len, print_option is_inner>
auto BasicVec<vec_value, len, is_inner>::operator[](int i) const -> vec_value
{
	return inner[i];
}
template<inner_type_accept vec_value, int len, print_option is_inner>
auto BasicVec<vec_value, len, is_inner>::operator[](int i) -> vec_value&
{
	return inner[i];
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, 3, is_inner> math::BasicVec<vec_value, len, is_inner>::cross(BasicVec<vec_value, 3, is_inner>& rhs) const
{
	auto res = BasicVec<vec_value, 3, is_inner>();
	res[0] = this->inner[1] * rhs[2] - this->inner[2] * rhs[1];
	res[1] = this->inner[2] * rhs[0] - this->inner[0] * rhs[2];
	res[2] = this->inner[0] * rhs[1] - this->inner[1] * rhs[0];
	return res;
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline double math::BasicVec<vec_value, len, is_inner>::length_squared() const
{
	double res = 0.0;
	for (int i = 0; i < len; i++) {
		res += this->inner[i] * this->inner[i];
	}
	return res;
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline double math::BasicVec<vec_value, len, is_inner>::length() const
{
	return sqrt(this->length_squared());
}

template<inner_type_accept vec_value, int len, print_option is_inner>
inline BasicVec<vec_value, len, is_inner> math::BasicVec<vec_value, len, is_inner>::unit_vec() const
{
	auto res = *this;
	res /= this->length();
	return res;
}
