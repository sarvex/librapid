#include <librapid/array/multiarray.hpp>
#include <librapid/array/ops.hpp>
#include <librapid/utils/array_utils.hpp>

namespace librapid
{
	// ========= Addition =========

	void add(const Array &a, const Array &b, Array &res)
	{
		Array::applyBinaryOp(a, b, res, ops::Add());
	}

	Array add(const Array &a, const Array &b)
	{
		return Array::applyBinaryOp(a, b, ops::Add());
	}

	Array Array::operator+(const Array &other) const
	{
		return add(*this, other);
	}

	// ========= Addition =========

	void sub(const Array &a, const Array &b, Array &res)
	{
		Array::applyBinaryOp(a, b, res, ops::Sub());
	}

	Array sub(const Array &a, const Array &b)
	{
		return Array::applyBinaryOp(a, b, ops::Sub());
	}

	Array Array::operator-(const Array &other) const
	{
		return sub(*this, other);
	}

	// ========= Multiplication =========

	void mul(const Array &a, const Array &b, Array &res)
	{
		Array::applyBinaryOp(a, b, res, ops::Mul());
	}

	Array mul(const Array &a, const Array &b)
	{
		return Array::applyBinaryOp(a, b, ops::Mul());
	}

	Array Array::operator*(const Array &other) const
	{
		return mul(*this, other);
	}

	// ========= Division =========

	void div(const Array &a, const Array &b, Array &res)
	{
		Array::applyBinaryOp(a, b, res, ops::Div());
	}

	Array div(const Array &a, const Array &b)
	{
		return Array::applyBinaryOp(a, b, ops::Div());
	}

	Array Array::operator/(const Array &other) const
	{
		return div(*this, other);
	}
}