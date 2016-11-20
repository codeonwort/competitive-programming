-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734E (Anton and Tree)

import Control.Exception
import Control.DeepSeq
import Control.Monad
import qualified Data.Sequence as Seq
import Data.Array
import Data.List
import Data.Maybe
import Data.Tuple (swap)
import Data.Foldable (toList)
import qualified Data.IntSet as Set
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt
type Graph = Array Int [Int]

main = do
	n <- getInt
	colors <- listArray (1,n) `fmap` getInts
	edges <- replicateM (n-1) $ do
		[u,v] <- getInts
		return (u,v)
	let edges' = edges ++ (map swap edges)
	let g = accumArray (flip (:)) [] (1,n) edges'
	--print $ (diameter h n + 1) `div` 2
	print $ (diameter g colors n + 1) `div` 2

-- this is the problem!!! very slow for large N
preorder :: Graph -> Int -> [(Int,Int)]
preorder g start = toList $ bfs Seq.empty [(start,start)] where
	bfs nodes [] = nodes
	bfs nodes queue = bfs (nodes Seq.>< Seq.fromList queue) (concatMap nexts queue)
	nexts (v,parent) = map (\u -> (u,v)) $ filter (/= parent) (g ! v)

--preorder g start = dfs start start where
--	dfs parent v = (v,parent) : concatMap (dfs v) (filter (/= parent) (g ! v))

levels :: Graph -> Array Int Int -> Int -> Int -> Array Int Int
levels g colors start n = a where
	a = array (1, n) [findLevel v | v <- order]
	findLevel (v, parent)
		| v == parent = (v, 0)
		| colors ! v == colors ! parent = (v, a ! parent)
		| otherwise = (v, (a ! parent) + 1)
	order = preorder g start

maxLevel g colors start n
	= maximumBy (\a b -> compare (snd a) (snd b)) $ assocs $ levels g colors start n

diameter :: Graph -> Array Int Int -> Int -> Int
diameter g colors n = snd $ maxLevel g colors (fst $ maxLevel g colors 1 n) n

{-
preorder :: Graph -> Int -> [(Int,Int)]
preorder g start = dfs Set.empty start start where
	dfs visited parent v = (v,parent) : concatMap (dfs visited' v) nexts where
		visited' = Set.insert v visited
		nexts = filter (`Set.notMember` visited) (g ! v)
-}

{-
compress :: Array Int Int -> Graph -> Int -> Int -> Graph
compress colors g start n = accumArray (flip (:)) [] (1,n) edges' where
	edges = map findRoot $ filter diffColor $ order
	edges' = edges ++ (map swap edges)
	findRoot (v,u) = (rootLink ! v, rootLink ! u)
	rootLink = array (1, n) $ map getRoot $ order
	getRoot (v, parent)
		| v == parent || diffColor (v, parent) = (v, v)
		| otherwise = (v, rootLink ! parent)
	diffColor (v,u) = colors ! v /= colors ! u
	order = preorder g start
levels :: Graph -> Int -> Int -> Array Int Int
levels g start n = a where
	a = array (1,n) [findLevel v | v <- preorder g start]
	--a = accumArray (flip const) (-1) (1,n) [findLevel v | v <- preorder g start]
	findLevel (v,parent)
		| v == parent = (v,0)
		| otherwise = (v, (a ! parent) + 1)
--maxLevel g start n = maximumBy (\a b -> compare (snd a) (snd b)) $ assocs $ levels g start n
-}

