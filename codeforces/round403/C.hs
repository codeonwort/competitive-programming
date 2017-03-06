-- Codeforces Round #403 (Div. 2)
-- C. Andryusha and Colored Balloons
-- http://codeforces.com/contest/782/problem/C

import Control.Exception
import Control.Monad
import Data.Tuple
import Data.Array
import Data.Maybe
import Data.Foldable (toList)
import qualified Data.IntSet as Set
import qualified Data.Sequence as Seq
import qualified Data.Map.Strict as Map
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

type Edge = (Int, Int)
type Graph = Array Int [Int]
type Visited = Set.IntSet
type ParentMapping = Array Int Int
type ColorTable = Map.Map Int Int

buildG :: [Edge] -> Int -> Graph
buildG es n = accumArray (flip (:)) [] (1,n) es

main = do
	n <- getInt								-- input
	edges <- replicateM (n-1) $ do
		[u,v] <- getInts
		return (u,v)
	let edges' = edges ++ map swap edges	-- construct the graph
	let graph = buildG edges' n
	let k = maxOutdegree graph + 1			-- calculate k
	let (colors,_,_) = colorize graph n k	-- colorize the graph
	print k									-- output
	forM [1..n] $ \i -> putStr (show (colors Map.! i)) >> putChar ' '

maxOutdegree :: Graph -> Int
maxOutdegree = maximum . map length . elems

colorize :: Graph -> Int -> Int -> (ColorTable, Visited, [Int])
colorize g n k = foldl visit (table0,Set.empty,cycle [1..k]) (preorder g 1) where
	table0 = Map.fromList [(v,0) | v <- [1..n]]
	parents = array (1,n) (preorder g 1)
	visit (table,visited,colors) (v,parent)
		| v `Set.member` visited = (table,visited,colors)
		| otherwise = (Map.insert v (head colors') table, v `Set.insert` visited, tail colors')
		where colors' = dropWhile (\c -> c == table Map.! (parents ! v) || c == table Map.! (parents ! (parents ! v))) colors

preorder :: Graph -> Int -> [(Int,Int)]
preorder g v0 = toList $ bfs Seq.empty [(v0,v0)] where
	bfs nodes [] = nodes
	bfs nodes queue = bfs (nodes Seq.>< Seq.fromList queue) (concatMap nexts queue)
	nexts (v,parent) = map (\u -> (u,v)) $ filter (/= parent) (g ! v)

