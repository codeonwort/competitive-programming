import Control.Monad

-- ID:	699B (One Bomb)
-- URL:	http://codeforces.com/problemset/problem/699/B

main = do
	[n,m] <- (map read . words) `fmap` getLine :: IO [Int]
	tbl <- (concat . lines) `fmap` getContents
	let ps = [(i,j) | i <- [1..n], j <- [1..m]]
	let walls = fst $ unzip $ filter (\(_,v) -> v == '*') (zip ps tbl)
	if walls == []
	then putStrLn "YES" >> putStrLn "1 1"	-- no wall. place the bomb anywhere
	else case search walls n m of			-- possible bomb installations
		[] -> putStrLn "NO"					-- no solution
		((y,x):xs) -> do
			putStrLn "YES"					-- print first solution
			putStrLn $ show y ++ " " ++ show x

search (w:walls) n m = f walls (bombs0 w) where
	-- f :: [wall] -> [bomb] -> [bomb]
	f [] ps = ps
	f _ [] = []
	f (w:ws) ps = f ws (cross w ps)
	cross (wy,wx) ps = filter (\(py,px) -> py == wy || px == wx) ps
	bombs0 (wy,wx) = [(y,wx) | y <- [1..n]] ++ [(wy,x) | x <- [1..m], x /= wx]
