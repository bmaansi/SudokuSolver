
func getSoduko(S) {
	get(dim)
	real(false)
	for (i(0) to dim)  //row
		for (j(0) to dim)  // col
			get(S[i][j])
			if get(S[i][j]) == 0 
				real == true
	if (!real) 
		"Invalid or already solved"
}
	

func Validator(S, col, row, num, dim) {
	d = sqrt(dim)
	return (InBox(S, row - (row % d), col - (col % d), num, d) 
		|| InColumn(S, col, num, dim) || InRow(S, row, num, dim));
}


func InBox(S, int row, int col, int num, int d) {
	for (r(0) to d) 
		for (c(0) to d)
			if S[row + r][col + c] == num
				return true
	return false
}

func InColumn(S, int col, int num, int dim) {
	for (row(0) to dim) 
		if (num == S[row][col]) 
			return true
	return false
}

func InRow(S, int row, int num, int dim) {
	for (col(0) to dim) 
		if (num == S[row][col])
			return true
	
	return false
}


func SudokuSolver(S, row, col, dim) {
	if (row == dim - 1 && col == dim)
		return true

	if (col == dim) 
		col = 0
		row = row + 1

	if (S[row][col] != 0)  //not a blank spot
		return SudokuSolver(S, row, col + 1, dim)

	for (num(1) to dim) 
		if (!Validator()) //means number is valid
			S[row][col] = num
			if (SudokuSolver(S, row, col + 1, dim)) {
				return true
			}
		S[row][col] = 0 //it will be blank again 

	return false
}

func print(S, dim) {
	for (i(0) < dim) 
		for (j(0) < dim) 
			print(S[i][j], " ")		
		print(newline)
	}
}