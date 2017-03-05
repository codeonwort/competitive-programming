-- ID:	702E (Analysis of Pathes in Functional Graph)
-- URL:	http://codeforces.com/contest/702/problem/E

{-
Memory saving: Node - unpack and use strict fields
Time saving:   fully evaluate all arrays (force)
-}

{-# LANGUAGE BangPatterns #-}

import Control.Monad
import Data.Maybe
import Data.Array
import Data.Int
import Data.Char
import Numeric
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import Control.Exception
import Control.DeepSeq

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]
getInt64s = (map (fromIntegral . fst . fromJust . BS8.readInteger) . BS8.words) `fmap` BS.getLine :: IO [Int64]

data Node = Node {-# UNPACK #-} !Int {-# UNPACK #-} !Int64 {-# UNPACK #-} !Int64 -- (to, cost, minWeight)
instance NFData Node where
	rnf (Node a b c) = rnf a `seq` rnf b `seq` rnf c
type State = Array Int Node

toBinary :: Int64 -> String
toBinary x = showIntAtBase 2 intToDigit x ""

valid (state, digit) = digit == '1'

main = do
	[n', k'] <- words `fmap` getLine
	let n = read n' :: Int
	let k = read k' :: Int64
	let pos = toBinary k
	evaluate pos
	nexts <- listArray (0,n-1) `fmap` getInts :: IO (Array Int Int)
	costs <- listArray (0,n-1) `fmap` getInt64s :: IO (Array Int Int64)
	let state0 = initState n nexts costs
	let states = scanl (step n) state0 [1..length pos-1]
	let valids = fst $ unzip $ filter valid (zip states (reverse pos))
	let soln = findSoln valids n
	evaluate $ force states
	evaluate $ force valids
	evaluate $ force soln
	forM_ [0..n-1] $ \i -> do
		let Node _ !si !mi = soln ! i
		putStr (show si)
		putChar ' '
		putStrLn (show mi)

-- num nodes, next nodes, edge weights -> initial iteration (state after very first move)
initState :: Int -> Array Int Int -> Array Int Int64 -> State
initState n nexts costs = listArray (0,n-1) [Node (nexts ! i) cost cost | i <- [0..n-1], let cost = costs ! i]

step :: Int -> State -> Int -> State
step n state _ = listArray (0,n-1) [f i | i <- [0..n-1]] where
	f i = Node to2 (len1+len2) (min min1 min2) where
		Node to1 len1 min1 = state ! i
		Node to2 len2 min2 = state ! to1

findSoln :: [State] -> Int -> Array Int Node
findSoln states n = f states $ listArray (0,n-1) [Node i 0 (10^8+1) | i <- [0..n-1]] where
	f [] soln = soln
	f (st:states) curr = f states $
		listArray (0,n-1) [Node to1 (s+len1) (min m min1) | i <- [0..n-1],
							let Node to s m = curr ! i,
							let Node to1 len1 min1 = st ! to]
