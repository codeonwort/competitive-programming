import Control.Monad
import Data.Array
import Data.List
import Numeric

-- ID:	ARCTIC
-- URL:	https://algospot.com/judge/problem/read/ARCTIC

getInt = read `fmap` getLine :: IO Int

main = do
	n <- getInt
	replicateM_ n solve

solve = do
	n <- getInt
	points <- map (map read . words) `fmap` replicateM n getLine :: IO [[Float]]
	putStrLn $ round3 $ soln points

distances points = a where
	a = array ((1,1),(n,n)) (calc $ zip points [1..n]) 
	n = length points
	calc pts = do
		([x1,y1], i) <- pts
		([x2,y2], j) <- pts
		return ((i,j), sqrt $ (x2-x1) ** 2 + (y2-y1) ** 2)

{- Bellman-Ford Algorithm - slightly slow
shortests distances n start = [a ! (i, n-1) | i <- [1..n]] where
	a = array ((1,1),(n,n-1)) ls
	ls = [((i,j), d i j) | i <- [1..n], j <- [1..n-1]]
	cost i j = distances ! (i, j)
	d i 1 = cost start i
	d i j = minimum [a ! (k, j-1) `max` cost k i | k <- [1..n]]
-}

{- Floyd-Warshall Algorithm - too slow
shortests2 distances n start = [a ! (start, i, n) | i <- [1..n]] where
	a = array ((1,1,0),(n,n,n)) ls
	ls = [((i,j,k), d i j k) | i <- [1..n], j <- [1..n], k <- [0..n]]
	cost i j = distances ! (i, j)
	d i j 0 = cost i j
	d i j k = min (a ! (i,j,k-1)) ((a ! (i,k,k-1)) `max` (a ! (k,j,k-1)))
-}

replace xs i x = let (ys, zs) = splitAt (i-1) xs in ys ++ x : tail zs
dijkstra :: Array (Int,Int) Float -> Int -> Int -> [Float]
dijkstra distances n start = f (replicate n False) [if i == start then 0.0 :: Float else 99999.0 | i <- [1..n]] where
	-- f :: [visited] -> [minDist] -> [minDist]
	f visited dists = case findMin visited dists of
		(_, _, -1) -> dists
		(_, minD, i) -> f (replace visited i True) [ if v then dist else min dist (max (distances ! (i,j)) minD) | (v,dist,j) <- zip3 visited dists [1..n]]
	findMin visited dists =
		let cand = filter (\(v,d,i) -> not v) $ zip3 visited dists [1..n]
		in  if length cand == 0 then (True,0,-1) else minimumBy (\(v1,d1,i1) (v2,d2,i2) -> compare d1 d2) cand

--soln points = maximum $ shortests (distances points) (length points) 1
soln points = maximum $ dijkstra (distances points) (length points) 1
round3 n = showGFloat (Just 2) n ""
