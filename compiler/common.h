struct location {
public:
    int _column;
    int _line;
    int _column_last;
    int _line_last;
    location() {
	_column = 1;
        _line = 0;
        _column_last = 1;
        _line_last = 0;
    }
};
