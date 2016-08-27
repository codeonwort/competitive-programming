import Data.Maybe
import Data.Array
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map
import qualified Data.IntSet as Set

-- ID:	707D (Persistent Bookcase)
-- URL:	http://codeforces.com/problemset/problem/707/D

-- This is not an accepted code: TLE

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

data Query = Set Int Int | Unset Int Int | Invert Int | Revert
data Bookcase = Bookcase {
	bookData :: Map.Map Int (Set.IntSet,Int,Bool),
	rows :: Int,
	cols :: Int
}
emptyBookcase n m = Bookcase (Map.fromList [(i,(Set.empty,0,False)) | i <- [1..n]]) n m

type Tree = Map.Map Int [(Int,Query)]

main = do
	[n,m,q] <- getInts
	queries <- replicateM q getInts
	let tree = mkTree queries :: Tree
	let soln = tail . elems $ solve n m q tree
	forM_ soln $ \s -> print s

mkTree queries = f tree0 1 queries where
	tree0 = Map.fromList [(i,[]) | i <- [0..length queries]]
	f tree _ [] = tree
	f tree nodeIx (q:qs) = case q of
		[1,i,j] -> f (set i j tree) (nodeIx+1) qs
		[2,i,j] -> f (unset i j tree) (nodeIx+1) qs
		[3,i] -> f (invert i tree) (nodeIx+1) qs
		[4,k] -> f (revert k tree) (nodeIx+1) qs
		where
			set i j tree = Map.adjust ((nodeIx, Set i j):) (nodeIx-1) tree
			unset i j tree = Map.adjust ((nodeIx, Unset i j):) (nodeIx-1) tree
			invert i tree = Map.adjust ((nodeIx, Invert i):) (nodeIx-1) tree
			revert k tree = Map.adjust ((nodeIx, Revert):) k tree

solve :: Int -> Int -> Int -> Tree -> Array Int Int
solve n m q tree = array (0,q) (dfs (emptyBookcase n m) 0 0) where
	dfs bookcase ix acc
		| isLeaf = [(ix, acc)]
		| otherwise = (ix,acc) : concat [dfs book' nodeIx acc' | (nodeIx, query) <- children, let (book',acc') = apply query (bookcase,acc)]
		where
			isLeaf = null (tree Map.! ix)
			children = tree Map.! ix :: [(Int,Query)]

apply :: Query -> (Bookcase,Int) -> (Bookcase,Int)
apply (Set i j) (book, acc)
	| j `Set.member` row && not inverted = (book, acc)
	| j `Set.notMember` row && inverted = (book, acc)
	| not inverted = (book { bookData = Map.adjust (\(row,sz,inverted) -> (Set.insert j row, sz+1, inverted)) i (bookData book) }, acc+1)
	| inverted = (book { bookData = Map.adjust (\(row,sz,inverted) -> (Set.delete j row, sz-1, inverted)) i (bookData book) }, acc+1)
	where (row, size, inverted) = bookData book Map.! i
apply (Unset i j) (book, acc)
	| j `Set.notMember` row && not inverted = (book, acc)
	| j `Set.member` row && inverted = (book, acc)
	| not inverted = (book { bookData = Map.adjust (\(row,sz,inverted) -> (Set.delete j row, sz-1, inverted)) i (bookData book) }, acc-1)
	| inverted = (book { bookData = Map.adjust (\(row,sz,inverted) -> (Set.insert j row, sz+1, inverted)) i (bookData book) }, acc-1)
	where (row, size, inverted) = bookData book Map.! i
apply (Invert i) (book, acc) = (book', acc') where
	book' = book { bookData = Map.adjust (\(row,sz,inverted) -> (row, sz, not inverted)) i (bookData book) }
	acc' = acc + cols book - 2 * rowSize
	(row, size, inverted) = bookData book Map.! i
	rowSize
		| not inverted = size
		| otherwise = cols book - size
apply Revert x = x
