-- ID:  TRAVERSAL (트리 순회 순서 변경)
-- URL: https://algospot.com/judge/problem/read/TRAVERSAL

import Data.List
import Data.Maybe
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	numTests <- getInt
	replicateM_ numTests solve

solve = do
	n <- getInt
	preorder <- getInts
	inorder <- getInts
	let tree = build preorder inorder
	let postorder = visitPostorder tree
	forM_ postorder $ \k -> do
		putStr (show k)
		putChar ' '
	putChar '\n'

data Tree = Empty | Branch Int Tree Tree

build [] _ = Empty
build [x] _ = Branch x Empty Empty
build preorder@(p:ps) inorder = Branch p lt rt where
	lt = build (take p_in ps) (take p_in inorder)
	rt = build (drop p_in ps) (drop (p_in+1) inorder)
	p_in = fromJust (findIndex (== p) inorder)

visitPostorder Empty = []
visitPostorder (Branch k lt rt) = visitPostorder lt ++ visitPostorder rt ++ [k]
