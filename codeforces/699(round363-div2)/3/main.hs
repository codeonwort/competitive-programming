-- ID:	699C (Vacations)
-- URL:	http://codeforces.com/contest/699/problem/C

-- note: greedy algorithm
-- reference: http://codeforces.com/contest/699/submission/19751296

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	ns <- (map read . take n . words) `fmap` getContents :: IO [Int]
	print $ solve ns

{- input
0: no gym, no contest
1: no gym, yes contest
2: yes gym, no contest
3: yes gym, yes contest
-}

inf = 10000

-- f events [a0, a1, a2]
-- a0: when do rest on i-th day, the minimal rest
-- a1: when go to gym on i-th day, the minimal rest
-- a2: when participate in contest on i-th day, the minimal rest
solve ns = f ns [0,inf,inf] where
	f [] xs = minimum xs
	f (n:ns) xs
		| n == 0 = f ns [minimum xs + 1, inf, inf]
		| n == 1 = f ns [minimum xs + 1, inf, minimum [xs!!0, xs!!1]]
		| n == 2 = f ns [minimum xs + 1, minimum [xs!!0, xs!!2], inf]
		| n == 3 = f ns [minimum xs + 1, minimum [xs!!0, xs!!2], minimum [xs!!0, xs!!1]]
