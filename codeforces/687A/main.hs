import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

-- ID:	687A (NP-Hard Problem)
-- URL:	http://codeforces.com/problemset/problem/687/A

-- Strategy: brute force
-- This is not an accepted code
-- TLE on test 12 (n:20, m:22)

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

subsets [] = [[]]
subsets (x:xs) = xss ++ map (x:) xss where xss = subsets xs

xs `minus` [] = xs
(x:xs) `minus` yss@(y:ys)
	| x == y = xs `minus` ys
	| otherwise = x : xs `minus` yss

isCover :: [Int] -> [[Int]] -> Bool
isCover verts edges = all (\[u,v] -> u `elem` verts || v `elem` verts) edges

vertexCovers subs edges = filter (\(x,y) -> isCover x edges && isCover y edges) subs

main = do
	-- num of vertices, num of edges
	[n, m] <- getInts
	edges <- replicateM m getInts
	let verts = [1..n]
	let xs = subsets verts
	let subs = concatMap (\x -> [(x,y) | y <- subsets (verts `minus` x)]) xs
	let soln = vertexCovers subs edges
	if soln == []
	then print (-1)
	else do
		let (x,y) = head soln
		print (length x)
		forM_ x $ \i -> putStr (show i) >> putChar ' '
		putStrLn ""
		print (length y)
		forM_ y $ \j -> putStr (show j) >> putChar ' '
		putStrLn ""
