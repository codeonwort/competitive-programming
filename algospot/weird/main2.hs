import Control.Monad
import Data.List

-- another solution for WEIRD

getInt = read `fmap` getLine :: IO Int

main = do
	--forM_ [10000000..10000130] $ \i -> do
	--	when (weird i) (print i)
	numCases <- getInt
	replicateM_ numCases solve

solve = do
	num <- getInt
	if weird num
	then putStrLn "weird"
	else putStrLn "not weird"

weird n = abundant n && (not $ semiperfect n)

sqrt_int = floor . sqrt . fromIntegral
properDivisors :: Int -> [Int]
properDivisors n = 1 : halves ++ (if squared then [sqrt_int n] else []) ++ map (\i -> n `div` i) (reverse halves) where
	halves = [x | x <- [2..m], n `mod` x == 0]
	squared = (sqrt_int n) * (sqrt_int n) == n
	m = if squared then sqrt_int n - 1 else sqrt_int n

abundant n = sum (properDivisors n) > n
semiperfect n = knapsack0 n (properDivisors n)

knapsack0 n divs = table (length divs) n where
	table _ 0 = True
	table 1 1 = True
	table 1 j = False
	table i j
		| si > j = table (i-1) j
		| otherwise = table (i-1) (j-si) || table (i-1) j
		where si = divs !! (i-1)
