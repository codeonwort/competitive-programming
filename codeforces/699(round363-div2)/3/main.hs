import Debug.Trace

-- ID:	699C (Vacations)
-- URL:	http://codeforces.com/contest/699/problem/C

-- This is not a valid code! --
-- note: greedy algorithm    --

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	ns <- (take n . map read . words) `fmap` getContents :: IO [Int]
	print $ solve ns

{-
0: no gym, no cont
1: no gym, yes cont
2: yes gym, no cont
3: yes gym, yes cont
-}

-- from [0,1,2,3] to 0 is possible
-- from [0,2,3] to 1 is possible
-- ...
possibles = [[0,1,2,3], [0,2,3], [0,1,3], [0,1,2,3]]

-- given i, one can do o?
possible i o = i == 3 || o == 0 || i == o
cost x = if x == 0 then 1 else 0

solve (n:ns) = f ns (cost0 n) where
	cost0 n0 = map (\x -> if possible n0 x then cost x else -1) [0..3]
	f [] xs = minimum $ filter (/= -1) xs
	f (n:ns) xs = trace (show xs) $ f ns ys where
		ys = [if possible n x then minPrev x + cost x else -1 | x <- [0..3]]
		minPrev x = minimum [xs !! y | y <- (possibles !! x), (xs !! y) /= -1]
