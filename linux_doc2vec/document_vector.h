typedef struct{
	int id; // term id
	int count; // count
}document_element_t;

typedef struct {
	int length; // number of elements
	struct document_element_t* elements;
}document_vector_t;
