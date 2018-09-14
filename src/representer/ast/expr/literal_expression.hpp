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

#ifndef AVALON_AST_EXPR_LITERAL_EXPRESSION_HPP_
#define AVALON_AST_EXPR_LITERAL_EXPRESSION_HPP_

#include <cstddef>
#include <memory>
#include <string>

#include <boost/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "representer/ast/expr/expr.hpp"
#include "representer/ast/decl/type.hpp"
#include "lexer/token.hpp"


namespace avalon {
    enum literal_expression_type {
        INTEGER_EXPR,
        DECIMAL_EXPR,
        FLOATING_POINT_EXPR,
        STRING_EXPR,
        BIT_EXPR,
        QUBIT_EXPR,
    };

    class literal_expression : public expr {
    public:
        /**
         * the constructor expects the token with source code information
         */
        literal_expression(token& tok, literal_expression_type expr_type, const std::string& val);

        /**
         * copy constructor
         */
        literal_expression(const std::shared_ptr<literal_expression>& lit_expr);

        /**
         * assignment copy operator
         */
        literal_expression& operator=(const std::shared_ptr<literal_expression>& lit_expr);

        /**
         * get_token
         * returns a token with type source information
         */
        const token& get_token() const;

        /**
         * set_type_instance
         * sets the type instance of this expression
         */
        void set_type_instance(type_instance& instance);

        /**
         * set_type_instance
         * sets the type instance of this expression with the possibility of specifying
         * if the parser (true case) set the type instance or the inference engine (false case)
         */
        void set_type_instance(type_instance& instance, bool from_parser);

        /**
         * get_type_instance
         * returns the type instance of this expression
         */
        type_instance& get_type_instance();

        /**
         * has_type_instance
         * returns true if the type instance is not star
         */
        bool has_type_instance();

        /**
         * type_instance_from_parser
         * returns true if the type instance was set by the parser
         * this will happen when the user specifies a type directly on an expression
         */
        bool type_instance_from_parser() const;

        /**
         * get_expression_type
         * returns the type of literal this expression holds
         */
        const literal_expression_type& get_expression_type() const;

        /**
         * get_value
         * returns the string representing the value stored within this literal
         */
        const std::string& get_value() const;

        /**
         * get_int_value
         * returns the integer representation of this literal if it is an integer
         * throws a value_error exception if an attempt to retreive the wrong value type is attempted
         */
        long long int get_int_value();

        /**
         * get_dec_value
         * returns the decimal representation of this literal if it is a decimal
         * throws a value_error exception if an attempt to retreive the wrong value type is attempted
         */
        boost::multiprecision::cpp_dec_float_100 get_dec_value();

        /**
         * get_float_value
         * returns the double-precision representation of this literal
         * throws a value_error exception if it contains a different literal type
         */
        double get_float_value();

        /**
         * get_string_value
         * returns the string representation of this literal
         * throws a value_error exception if it contains a different literal type
         */
        std::string get_string_value();

        /**
         * get_bit_value
         * returns the bitset representating of this literal
         * throws a value_error exception if it contains a different literal type
         */
        boost::dynamic_bitset<> get_bit_value();

        /**
         * token
         * returns this expression token
         * this is useful because it prevents us from casting each expression just to display error messages
         */
        virtual const token& expr_token() const {
            return m_tok;
        }

        /**
         * expr_type_instance
         * returns the type instance of this expression, bypassing casting
         */
        virtual type_instance& expr_type_instance() {
            return m_instance;
        }

        /**
         * has_match_expression
         * returns true if the current expression depends on a match expression
         * this is useful during checking to make sure that variables and function parameters are not initialized with expressions containing match expressions
         */
        virtual bool has_match_expression() {
            return false;
        }
        
        /**
         * is_literal_expression
         * returns true as this is an literal expression
         */
        virtual bool is_literal_expression() {
            return true;
        }

    private:
        /*
         * the token with source code information
         */
        token m_tok;

        /*
         * type instance of this expression
         */
        type_instance m_instance;

        /*
         * whether the type instance is from the parser
         */
        bool m_type_instance_from_parser;

        /*
         * the type of literal expression this is
         */
        literal_expression_type m_expr_type;

        /*
         * the string representation of the literal
         */
        std::string m_val;
    };
}

#endif
