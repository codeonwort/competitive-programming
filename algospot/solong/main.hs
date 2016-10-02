-- ID:  SOLONG (안녕히, 그리고 물고기는 고마웠어요!)
-- URL: https://algospot.com/judge/problem/read/SOLONG
-- Category: Trie

import Data.List
import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map
import Debug.Trace

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

data Trie = Node {
	children :: Map.Map Char Trie,
	first :: Int,		-- id of the word that visited this node at first
	terminate :: Int	-- id of the word that terminates here
} deriving (Show, Eq)

main = do
	tests <- getInt
	replicateM_ tests solve

solve = do
	[n, m] <- getInts
	input <- replicateM n (words `fmap` getLine)
	let input' = map (\[word,freq] -> (word, read freq :: Int)) input
	let input'' = map fst (sortBy compareInput input')
	let trie' = foldl insertWord emptyTrie (zip input'' [1..n])
	let trie = trie' { first = -1 }
	queries <- words `fmap` getLine
	print $ (m - 1) + sum (map (answer trie) queries)

answer trie query
	| node == Nothing || terminate (fromJust node) == -1 = length query
	| otherwise = queryWord trie query (terminate (fromJust node))
	where node = findWord trie query

----------------------------------------------------------------------------------------

emptyTrie = Node Map.empty (-1) (-1)

insertWord :: Trie -> (String, Int) -> Trie
insertWord trie ([], id) = trie { first = first', terminate = id } where
	first' = if first trie == -1 then id else first trie
insertWord trie ((w:ws), id) = trie { children = children', first = first' } where
	children' = Map.insert w (insertWord child (ws, id)) (children trie)
	first' = if first trie == -1 then id else first trie
	child
		| w `Map.member` children trie = children trie Map.! w
		| otherwise = emptyTrie

findWord :: Trie -> String -> Maybe Trie
findWord trie [] = Just trie
findWord trie (w:ws)
	| w `Map.member` children trie = findWord (children trie Map.! w) ws
	| otherwise = Nothing

queryWord :: Trie -> String -> Int -> Int
queryWord trie [] _ = 0
queryWord trie (w:ws) id
	| first trie == id = 1
	| otherwise = 1 + queryWord child ws id
	where child = children trie Map.! w

compareInput (w1,f1) (w2,f2) = case compare f2 f1 of
	EQ -> compareWord w1 w2
	x -> x

-- compareWord [] [] = EQ -- never happens in this problem
compareWord [] y = LT
compareWord x [] = GT
compareWord (x:xs) (y:ys) = case compare x y of
	EQ -> compareWord xs ys
	x -> x
