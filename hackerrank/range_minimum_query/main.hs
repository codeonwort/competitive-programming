-- ID:  Range Minimum Query
-- URL: https://www.hackerrank.com/challenges/range-minimum-query
-- Category: Functional Programming -> Functional Structures

import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import Control.Exception (evaluate)

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	[n,m] <- getInts -- num elements, num queries
	nums <- getInts
	let segTree = buildTree nums n
	evaluate segTree -- on my computer this is not needed, but on Hackerrank without this you get TLE. I don't know why. Maybe compiler settings are different?
	replicateM_ m $ do
		range <- getInts
		print $ query segTree range

-- recursive construction of a segment tree
-- see below for an iterative version
buildTree :: [Int] -> Int -> SegTree
buildTree nums n = f nums (0,n-1) where
	-- f [] _ = undefined -- WTF never use this line! severe performance down. anyway this case never matches
	f [x] (l,r) = Node (l,r,x) Empty Empty
	f xs (l,r) = Node (l,r,minLR) ltree rtree where
		mid = (l + r) `div` 2
		half = mid - l + 1
		ltree = f (take half xs) (l,mid)
		rtree = f (drop half xs) (mid+1,r)
		minLR = min (rangeMin ltree) (rangeMin rtree)

query :: SegTree -> [Int] -> Int
query Empty _ = 10^6 -- maximum element is 10^5
query (Node (rangeL, rangeR, minValue) ltree rtree) range@[l,r]
	| r < rangeL || rangeR < l		= 10^6
	| l <= rangeL && rangeR <= r	= minValue
	| otherwise						= min retL retR
	where
		retL = query ltree range
		retR = query rtree range

type NodeData = (Int, Int, Int) -- left, right, min
data SegTree = Empty | Node NodeData SegTree SegTree deriving Show
rangeMin (Node (_,_,x) _ _) = x

{- iterative construction of a segment tree
buildTree nums n = f tree0 where
	tree0 = [Node (i,i,x) Empty Empty | (i,x) <- zip [0..n-1] nums]
	collect [] = []
	collect [x] = [x]
	collect (x:y:xs) = merge x y : collect xs
	merge ltree@(Node (l1,r1,x) _ _) rtree@(Node (l2,r2,y) _ _) = Node (l1,r2,min x y) ltree rtree
	f [x] = x
	f xs = f (collect xs)
-}

{- tree depth tester
testDepth :: SegTree -> Int
testDepth tree = f tree 0 where
	f Empty x = x
	f (Node dat l r) x = max (f l (x+1)) (f r (x+1))
-}

