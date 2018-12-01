struct Field{
    1: string type;
    // If type is not one of the base types.
    2: optional string definition;
}

struct Monoid {
    // <INPUT_NAME>, <INPUT_TYPE>,
    // <STATE_NAME>, <STATE_TYPE>, <STATE_OTHER_NAME>, <STATE_OTHER_TYPE>
    // <OUTPUT_NAME>, <OUTPUT_TYPE>
    // are the macro substitutions available for code strings.
    // Functions and libraries that match the types/generic types can be used
    // freely, but should be linked at compile time.

    // AVG, SUM, COUNT, UNIQUE_COUNT, MIN, MAX, FIRST, LAST etc..
    1: string name;

    2: string state_type;
    3: optional string state_def;

    4: string output_type;
    5: optional string output_def;

    // If prepare and update are not specified, it implies,
    // that the input type is the same as output type.

    // input -> state
    10: optional string prepare_code;

    // &state -> input -> void
    11: optional string update_code;

    // state -> &state -> void
    12: string merge_code;

    // state -> output
    13: optional string output_code;
}