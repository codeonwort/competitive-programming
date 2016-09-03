import Control.Monad

getIntegers = (map read . words) `fmap` getLine :: IO [Integer]

main = do
	[n, baseX] <- getIntegers
	xs <- getIntegers
	[m, baseY] <- getIntegers
	ys <- getIntegers
	let x = calc baseX (zip xs [n-1,n-2..0])
	let y = calc baseY (zip ys [m-1,m-2..0])
	if x == y
	then putChar '='
	else if x < y
	then putChar '<'
	else putChar '>'

calc base xs = sum $ map (\(x,i) -> x * base^i) xs
