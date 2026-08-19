# Tannic


enum value {
    SCALAR,
    VECTOR,
    TENSOR,
    OPERATOR
};

struct tensor_t {
    enum type type;
    struct layout_t layout;
};

class Value {


};