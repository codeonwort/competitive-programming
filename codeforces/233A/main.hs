import Control.Monad
import Data.List

-- ID:	233A (Perfect Permutation)
-- URL:	http://codeforces.com/problemset/problem/233/A

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	if odd n
	then print (-1)
	else do
		let (evens, odds) = partition even [1..n]
		let soln = interleave evens odds
		forM_ soln $ \i -> putStr (show i) >> putChar ' '

interleave xs ys = f xs ys [] where
	f [] [] zs = zs
	f (x:xs) (y:ys) zs = x:y: f xs ys zs
