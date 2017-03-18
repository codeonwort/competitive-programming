-- Algospot (https://algospot.com)
-- ID:  MORDOR
-- URL: https://algospot.com/judge/problem/read/MORDOR

import Control.Monad
import Control.DeepSeq
import Control.Exception
import Data.Maybe
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map parseInt . BS8.words) `fmap` BS.getLine :: IO [Int]
parseInt = fst . fromJust . BS8.readInt

main = getInt >>= \n -> replicateM_ n solve

solve = do
	[n,q] <- getInts
	heights <- getInts
	let tree = buildTree heights n
	evaluate (force tree)
	replicateM_ q $ do
		range@[a,b] <- getInts
		let (low,high) = query tree range
		print $ high - low

-- left bound, right bound, minimum and maximum value in the range
type NodeData = (Int, Int, Int, Int)

data SegTree = Empty | Node NodeData SegTree SegTree
instance NFData SegTree where
	rnf (Node a b c) = rnf a `seq` rnf b `seq` rnf c
	rnf Empty = ()
rangeMin (Node (_,_,x,_) _ _) = x
rangeMax (Node (_,_,_,x) _ _) = x

buildTree :: [Int] -> Int -> SegTree
buildTree nums n = f nums (0,n-1) where
	f [x] (l,r) = Node (l,r,x,x) Empty Empty
	f xs (l,r) = Node (l,r,minLR,maxLR) ltree rtree where
		mid = (l + r) `div` 2
		half = mid - l + 1
		ltree = f (take half xs) (l,mid)
		rtree = f (drop half xs) (mid+1,r)
		minLR = min (rangeMin ltree) (rangeMin rtree)
		maxLR = max (rangeMax ltree) (rangeMax rtree)

query :: SegTree -> [Int] -> (Int, Int)
query Empty _ = (20000 + 10, -1)
query (Node (rangeL, rangeR, minValue, maxValue) ltree rtree) range@[l,r]
    | r < rangeL || rangeR < l = (20000 + 10, -1)
    | l <= rangeL && rangeR <= r = (minValue, maxValue)
    | otherwise = (min minL minR, max maxL maxR)
    where
        (minL, maxL) = query ltree range
        (minR, maxR) = query rtree range
