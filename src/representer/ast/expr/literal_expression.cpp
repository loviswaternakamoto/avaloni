/*
 *  This file is part of the Avalon programming language
 * 
 *  Copyright (c) 2018 Ntwali Bashige Toussaint
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <cstdlib>
#include <memory>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "representer/ast/expr/literal_expression.hpp"
#include "representer/exceptions/value_error.hpp"
#include "representer/ast/expr/expr.hpp"
#include "representer/ast/decl/type.hpp"
#include "lexer/token.hpp"


namespace avalon {
    /**
     * the constructor expects the operand of the literal operator
     */
    literal_expression::literal_expression(token& tok, literal_expression_type expr_type, const std::string& val) : m_tok(tok), m_type_instance_from_parser(false), m_expr_type(expr_type), m_val(val) {
    }

    /**
     * copy constructor
     */
    literal_expression::literal_expression(const std::shared_ptr<literal_expression>& lit_expr) : m_tok(lit_expr -> get_token()), m_instance(lit_expr -> get_type_instance()), m_type_instance_from_parser(lit_expr -> type_instance_from_parser()), m_expr_type(lit_expr -> get_expression_type()), m_val(lit_expr -> get_value()) {
    }

    /**
     * assignment copy operator
     */
    literal_expression& literal_expression::operator=(const std::shared_ptr<literal_expression>& lit_expr) {
        m_tok = lit_expr -> get_token();
        m_instance = lit_expr -> get_type_instance();
        m_type_instance_from_parser = lit_expr -> type_instance_from_parser();
        m_expr_type = lit_expr -> get_expression_type();
        m_val = lit_expr -> get_value();
        return * this;
    }

    /**
     * get_token
     * returns a token with type source information
     */
    const token& literal_expression::get_token() const {
        return m_tok;
    }

    /**
     * set_type_instance
     * sets the type instance of this expression
     */
    void literal_expression::set_type_instance(type_instance& instance) {
        m_instance = instance;
    }

    /**
     * set_type_instance
     * sets the type instance of this expression with the possibility of specifying
     * if the parser (true case) set the type instance or the inference engine (false case)
     */
    void literal_expression::set_type_instance(type_instance& instance, bool from_parser) {
        m_instance = instance;
        m_type_instance_from_parser = from_parser;
    }

    /**
     * get_type_instance
     * returns the type instance of this expression
     */
    type_instance& literal_expression::get_type_instance() {
        return m_instance;
    }

    /**
     * has_type_instance
     * returns true if the type instance is not star
     */
    bool literal_expression::has_type_instance() {
        if(m_instance.get_name() == "*")
            return false;
        else
            return true;
    }

    /**
     * type_instance_from_parser
     * returns true if the type instance was set by the parser
     * this will happen when the user specifies a type directly on an expression
     */
    bool literal_expression::type_instance_from_parser() const {
        return m_type_instance_from_parser;
    }

    /**
     * get_expression_type
     * returns the type of literal this expression holds
     */
    const literal_expression_type& literal_expression::get_expression_type() const {
        return m_expr_type;
    }

    /**
     * get_value
     * returns the literal operator operand
     */
    const std::string& literal_expression::get_value() const {
        return m_val;
    }

    /**
     * get_int_value
     * returns the integer representation of this literal if it is an integer
     * throws a value_error exception if an attempt to retreive the wrong value type is attempted
     */
    long long int literal_expression::get_int_value() {
        if(m_expr_type == INTEGER_EXPR) {
            char * end = NULL;
            long long int value = std::strtoll(m_val.c_str(), &end, 10);
            return value;
        }
        else {
            throw value_error("This literal expression doesn't contain an integer.");
        }
    }

    /**
     * get_dec_value
     * returns the decimal representation of this literal if it is a decimal
     * throws a value_error exception if an attempt to retreive the wrong value type is attempted
     */
    boost::multiprecision::cpp_dec_float_100 literal_expression::get_dec_value() {
        if(m_expr_type == DECIMAL_EXPR) {
            boost::multiprecision::cpp_dec_float_100 value(m_val);
            return value;
        }
        else {
            throw value_error("This literal expression doesn't contain a decimal.");
        }
    }

    /**
     * get_float_value
     * returns the double-precision representation of this literal
     * throws a value_error exception if it contains a different literal type
     */
    double literal_expression::get_float_value() {
        if(m_expr_type == FLOATING_POINT_EXPR) {
            double value = ::atof(m_val.c_str());
            return value;
        }
        else {
            throw value_error("This literal expression doesn't contain a decimal.");
        }
    }

    /**
     * get_string_value
     * returns the string representation of this literal
     * throws a value_error exception if it contains a different literal type
     */
    std::string literal_expression::get_string_value() {
        if(m_expr_type == STRING_EXPR) {
            return m_val;
        }
        else {
            throw value_error("This literal expression doesn't contain a string.");
        }
    }
}