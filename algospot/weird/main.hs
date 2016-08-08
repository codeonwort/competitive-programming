import Control.Monad
import Data.List
{-import Data.Array.IArray
import Data.Array.Unboxed
import Data.Array.MArray
import Data.Array.ST-}

-- ID:	WEIRD
-- URL:	https://algospot.com/judge/problem/read/WEIRD

getInt = read `fmap` getLine :: IO Int

main = do
	--forM_ [10000000..10050000] $ \i -> do
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
--semiperfect n = knapsack n (properDivisors n)
semiperfect n = knapsack2 n (reverse $ properDivisors n)

knapsack2 n divs = f [n] divs (sum divs) where
	f xs [] _ = any (== 0) xs
	f xs (d:ds) lim =
		let ys = filter (\y -> 0 <= y && y <= lim) (map (\x -> x - d) xs)
		in if (any (== 0) ys) then True else f (ys ++ xs) ds (lim-d)

{-
for :: Monad m => [a] -> (b -> Bool) -> (a -> m b) -> m [b]
for [] _ _ = return []
for (x:xs) test f = f x >>= \y ->
	if test y
	then for xs test f >>= \ys -> return (y:ys)
	else return []

knapsack :: Int -> [Int] -> Bool
knapsack n divs =
	let ary = runSTUArray $ do
		ary <- newArray (1,n) False
		writeArray ary 1 True
		for divs not $ \i -> do
			forM_ [n,n-1..i+1] $ \j -> do
				x <- readArray ary j
				y <- readArray ary (j-i)
				writeArray ary j (x || y)
			writeArray ary i True
			fin <- readArray ary n
			return False
		return ary
	in ary ! n
-}
