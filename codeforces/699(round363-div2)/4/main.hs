import Data.List

-- ID:	699D (Fix a Tree)
-- URL:	http://codeforces.com/contest/699/problem/D

-- This is not a valid code!

getInt = read `fmap` getLine :: IO Int

data Tree = Cycle [(Int,Int)] Int | NoCycle [(Int,Int)]

main = do
	n <- getInt
	ns <- (take n . map read . words) `fmap` getContents :: IO [Int]
	let forest = sortBy compareTree $ mkForest (zip [1..n] ns)
	let (cost, fixed) = revise forest
	print cost
	print $ elems $ array (1,n) fixed

hasCycle (Cycle _ _) = True
hasCycle (NoCycle _) = False

compareTree (NoCycle _) (Cycle _ _) = LT
compareTree (Cycle _ _) (NoCycle _) = GT
compareTree _ _ = EQ

mkForest ns = 

revise
compareTree
mkForest
