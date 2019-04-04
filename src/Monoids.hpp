#pragma once
#include <algorithm>
#include <functional>
#include "TDigest.h"

namespace monoids {

template<typename Input, typename State, typename Output>
class Monoid
{
public:
    virtual State init(Input&& input) const = 0;

    virtual void update(State& state, Input&& input) const = 0;

    virtual void merge(State& returned, State&& moved) const = 0;

    virtual Output finalize(State&& state) const = 0;
};

// we need the extra designation to make it work with code generation
template<typename Input, typename State, typename Output>
class Sum : public Monoid<Input, State, Output>
{
public:
    State init(Input&& input) const override final {
        return input;
    }

    void update(State& state, Input&& input) const override final {
        state += input;
    }

    void merge(State& returned, State&& moved) const override final {
        returned += moved;
    }

    Output finalize(State&& state) const override final {
        return state;
    }
};


// we need the extra designation to make it work with code generation
template<typename Input, typename State, typename Output>
class Avg : public Monoid<Input, State, Output>
{
public:
    State init(Input&& input) const override final {
        State state;
        state.sum = input;
        state.count = 1;
        return state;
    }

    void update(State& state, Input&& input) const override final {
        state.sum += input;
        state.count++;
    }

    void merge(State& returned, State&& moved) const override final {
        returned.sum += moved.sum;
        returned.count += moved.count;
    }

    Output finalize(State&& state) const override final {
        return ((Output) state.sum) /((Output) state.count);
    }
};

template<typename Input, typename State, typename Output>
class Count : public Monoid<Input, State, Output>
{
public:
    State init(Input&& input) const override final {
        return 1;
    }

    void update(State& state, Input&& input) const override final {
        state++;
    }

    void merge(State& returned, State&& moved) const override final {
        returned += moved;
    }

    Output finalize(State&& state) const override final {
        return state;
    }
};

template<typename Input, typename State, typename Output>
class UniqueCount : public Monoid<Input, State, Output>
{
public:
    State init(Input&& input) const override final {
        State state {input};
        return state;
    }

    void update(State& state, Input&& input) const override final {
        state.insert(input);
    }

    void merge(State& returned, State&& moved) const override final {
        returned.insert(moved.begin(), moved.end());
    }

    virtual Output finalize(State&& state) const override final {
        return state.size();
    }
};




// Approximate Quantile monoid based on TDigest implementation by Derrick Burns
template<typename Input, typename Double, typename Double>
class Quantile : public Monoid<Input, Double, Double>
{
public:
    State init(Input&& input) const override final {
        State state {input};
        return state;
    }

    void update(State& state, Input&& input) const override final {
        state.insert(input);
    }

    void merge(State& returned, State&& moved) const override final {
        returned.insert(moved.begin(), moved.end());
    }

    virtual Output finalize(State&& state) const override final {
        return state.size();
    }
};


// Moments
template<typename Input, typename Double, typename Double>
class MomentMonoid : public Monoid<Double, Double, Double>
{
public:
    State init(Input&& input) const override final {
        State state {input};
        return state;
    }

    void update(State& state, Input&& input) const override final {
        state.insert(input);
    }

    void merge(State& returned, State&& moved) const override final {
        returned.insert(moved.begin(), moved.end());
    }

    virtual Output finalize(State&& state) const override final {
        return state.size();
    }
};

// TODO: Approx unique - hll-tailcut+ 2017 paper: better with fewer bits

/*

*/
}