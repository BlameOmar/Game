/**************************************************************************************************
 * Title:         abstract_vector.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-24
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "abstract_vector.h"

#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <stdexcept>

namespace evansbros { namespace math {

    real & abstract_vector::operator()(natural i)
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real   abstract_vector::operator()(natural i) const
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real & abstract_vector::operator[](natural i)
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    real   abstract_vector::operator[](natural i) const
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }

        return components()[i];
    }

    real * abstract_vector::begin()
    {
        return components();
    }

    real const * abstract_vector::begin() const
    {
        return components();
    }

    real const * abstract_vector::cbegin() const
    {
        return begin();
    }

    real * abstract_vector::end()
    {
        return components() + size();
    }

    real const * abstract_vector::end() const
    {
        return components() + size();
    }

    real const * abstract_vector::cend() const
    {
        return end();
    }

    real abstract_vector::get1Norm() const 
    {
        std::vector<real> temp(size());

        std::transform(begin(), end(), temp.begin(), [](real x) { return std::abs(x); });
        return std::accumulate(temp.begin(), temp.end(), 0.0f, [](real x, real y) { return x + y; });
    }

    real abstract_vector::get2Norm() const 
    {
        std::vector<real> temp(size());

        std::transform(begin(), end(), temp.begin(), [](real x) { return x * x; });
		return std::sqrt(std::accumulate(temp.begin(), temp.end(), 0.0f, [](real x, real y) { return x + y; }));
    }

    real abstract_vector::getUniformNorm() const 
    {
        std::vector<real> temp(size());

        std::transform(begin(), end(), temp.begin(), [](real x) { return std::abs(x); });
        return std::accumulate(temp.begin(), temp.end(), 0.0f, [](real x, real y) { return std::fmax(x, y); });
    }

    real abstract_vector::getPNorm(real p) const 
    {
        std::vector<real> temp(size());

        transform(begin(), end(), temp.begin(), [&](real x) { return std::pow(std::abs(x), p); });
		return std::pow(std::accumulate(temp.begin(), temp.end(), 0.0f, [](real x, real y) { return x + y; }), 1.0f / p);
    }

    void abstract_vector::add_to(abstract_vector * u, const abstract_vector * v)
    {
        if (u->size() != v->size()) {
            throw std::domain_error("Vectors differ in dimension.");
        }

        for (natural i = 0; i < u->size(); ++i) {
            u->operator()(i) += v->operator()(i);
        }
    }

    void abstract_vector::subtract_from(abstract_vector * u, const abstract_vector * v)
    {
        if (u->size() != v->size()) {
            throw std::domain_error("Vectors differ in dimension.");
        }

        for (natural i = 0; i < u->size(); ++i) {
            u->operator()(i) -= v->operator()(i);
        }
    }

    void abstract_vector::scale_by(abstract_vector * u, const real c) 
    {
        std::transform(u->begin(), u->end(), u->begin(), [&](real x) { return x * c; });
    }

    void abstract_vector::negate(abstract_vector *u) 
    {
        std::transform(u->begin(), u->end(), u->begin(), [](real x) { return -x; });
    }

} }
