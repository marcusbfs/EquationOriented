subroutine smul(mat, nrow, ncol, vec, res)
	real*8, intent(out) :: res(nrow)
	real*8, intent(in) :: mat(nrow, ncol) , vec(ncol)
	res = matmul(mat, vec)
end subroutine