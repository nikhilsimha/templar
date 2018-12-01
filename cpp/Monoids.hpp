#pragma once
#include <algorithm>
#include <functional>

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

    virtual Output finalize(State&& state) const override final {
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

    virtual Output finalize(State&& state) const override final {
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

    virtual Output finalize(State&& state) const override final {
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

template<typename Input, typename State, typename Output>
class OrderBy : public Monoid<Input, State, Output>
{
private:
    size_t _limit;
    bool _ascending; // = bottom, desceding = top

public:
    explicit OrderBy(size_t limit, bool ascending) :
    _limit(limit), _ascending(ascending) {}

    // statetype has to be a vector of input - or template substitution will fail.
    State init(Input&& input) const override final {
        State state;
        state.reserve(_limit);
        state.emplace_back(input);
        return state;
    }

    auto inputComparator() const {
        return [ascending = _ascending](const Input& first, const Input& second) {
            if(ascending) return first.key < second.key;
            return first.key > second.key;
        };
    }

    void prune_heap(State& state) const {
        while(state.size() > _limit) {
            std::pop_heap(
                state.begin(),
                state.end(),
                inputComparator()
            );
            state.pop_back();
        }
    }

    void update(State& state, Input&& input) const override final {
        state.emplace_back(input);
        std::push_heap(
            state.begin(),
            state.end(),
            inputComparator()
        );
        prune_heap(state);
    }

    void merge(State& returned, State&& moved) const override final {
        returned.reserve(returned.size() + moved.size());
        returned.insert(returned.end(), moved.begin(), moved.end());
        std::make_heap(returned.begin(), returned.end(), inputComparator());
        prune_heap(returned);
    }

    virtual Output finalize(State&& state) const override final {
        std::sort_heap(
            state.begin(),
            state.end(),
            inputComparator());
        Output output;
        output.reserve(state.size());
        for(auto&& elem: state) {
            output.emplace_back(std::move(elem.value));
        }
        return output;
    }
};
}