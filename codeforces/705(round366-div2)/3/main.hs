import Data.Maybe
import Data.List
import Control.Monad
import qualified Data.ByteString as BS
import qualified Data.ByteString.Char8 as BS8
import qualified Data.Map.Strict as Map
import qualified Data.IntSet as Set

-- ID:	705C (Thor)
-- URL:	http://codeforces.com/contest/705/problem/C

-- This is not an accepted code!
-- Holy s**t TLE on the very final test - test 60 !!!!! I hate Haskell !!!!!!

type State = (Map.Map Int (Queue Int), Queue (Int,Int), Int, Int, Map.Map Int Bool)
	-- (app->noti map, type1-event queue, num unread, current type1-event index, noti->visited map)

getInt = read `fmap` getLine :: IO Int
getInts = (map (fst . fromJust . BS8.readInt) . BS8.words) `fmap` BS.getLine :: IO [Int]

main = do
	[n,q] <- getInts
	events <- replicateM q getInts
	let book = Map.fromList [(k,emptyQ) | k <- [1..n]]
	let visited = Set.empty
	solve events (book, emptyQ, 0, 1, visited)

solve [] _ = return ()
solve (e:es) (book, notiQ, unread, type1_idx, visited) = do
	let [etype, evalue] = e
	if etype == 1
	then do
		let book' = Map.update (\q -> Just (pushQ type1_idx q)) evalue book
		let notiQ' = pushQ (type1_idx, evalue) notiQ
		print (unread + 1)
		solve es (book', notiQ', (unread + 1), type1_idx + 1, visited)
	else if etype == 2
	then do
		let app = evalue
		let toRead = book Map.! app
		let book' = Map.update (\_ -> Just emptyQ) app book
		let unread' = unread - lengthQ toRead
		let visited' = clearApp visited toRead
		print unread'
		solve es (book', notiQ, unread', type1_idx, visited')
	else do
		let (notiQ', visited', book', numRead) = readNotiQ evalue notiQ visited book 0
		let unread' = unread - numRead
		print unread'
		solve es (book', notiQ', unread', type1_idx, visited')

clearApp visited notiQ
	| isEmptyQ notiQ = visited
	| otherwise = clearApp (Set.insert noti visited) notiQ'
	where (noti,notiQ') = popQ notiQ

readNotiQ t notiQ visited book numRead
	| isEmptyQ notiQ = (notiQ, visited, book, numRead)
	| i > t = (notiQ, visited, book, numRead)
	| otherwise = readNotiQ t notiQ' visited' book' numRead'
	where
		((i,x),notiQ') = popQ notiQ
		already = Set.member i visited
		visited' = Set.insert i visited
		numRead' = if already then numRead else numRead + 1
		book' = if already then book else Map.update (\q -> Just (snd $ popQ q)) x book

-- implementation of queue
data Queue a = Queue [a] [a] Int deriving (Eq, Show)

emptyQ :: Queue a
emptyQ = Queue [] [] 0

pushQ :: a -> Queue a -> Queue a
pushQ x (Queue ins outs n) = Queue (x:ins) outs (n+1)

popQ :: Queue a -> (a, Queue a)
popQ (Queue ins [] n) = popQ $ Queue [] (reverse ins) n
popQ (Queue ins outs n) = (head outs, Queue ins (tail outs) (n-1))

isEmptyQ :: Queue a -> Bool
isEmptyQ (Queue [] [] 0) = True
isEmptyQ _ = False

lengthQ :: Queue a -> Int
lengthQ (Queue ins outs n) = n
