package com.cpgf.metagen;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import com.cpgf.metagen.metadata.CppClass;
import com.cpgf.metagen.metadata.DeferClass;
import com.cpgf.metagen.metadata.EnumVisibility;
import com.cpgf.metagen.metadata.Item;

public class Util {
	private static int currentUniqueID = 0;

	public static int getUniqueID() {
		++currentUniqueID;
		return currentUniqueID;
	}
	
	public static void trace(String message) {
		System.out.println(message);
	}

	public static void error(String message) throws MetaException {
		throw new MetaException(message);
	}

	public static String getAttribute(Node node, String attributeName) {
		return node.getAttributes().getNamedItem(attributeName).getNodeValue();
	}

	public static Node getNode(Node node, String nodeName) {
		List<Node> childList = getChildNodesByName(node, nodeName);
		if(childList.size() > 0) {
			return childList.get(0);
		}
		else {
			return null;
		}
	}

	public static String getNodeText(Node node) {
		if(node == null) {
			return null;
		}

		String result = "";
		NodeList childList = node.getChildNodes();
		
		for(int i = 0; i < childList.getLength(); ++i) {
			Node child = childList.item(i);
			if(child.getNodeName().equals("#text")) {
				result = result + child.getNodeValue();
			}
			else {
				result = result + getNodeText(child);
			}
		}

		return result;
	}

	public static List<Node> getChildNodesByName(Node node, String name) {
		List<Node> result = new ArrayList<Node>();
		
		NodeList childList = node.getChildNodes();
		
		for(int i = 0; i < childList.getLength(); ++i) {
			Node child = childList.item(i);
			if(child.getNodeName().equals(name)) {
				result.add(child);
			}
		}

		return result;
	}
	
	public static boolean isValueYes(String value) {
		return ! value.toLowerCase().equals("no");
	}
	
	public static <T extends Item> Item findItemByName(List<T> itemList, String name) {
		for(int i = 0; i < itemList.size(); ++i) {
			String itemName = itemList.get(i).getLiteralName();
			if(itemName != null && itemName.equals(name)) {
				return itemList.get(i);
			}
		}
		
		return null;
	}

	public static String readTextFromFile(String fileName) throws Exception {
	    BufferedReader bufferReader = new BufferedReader(new FileReader(fileName));
	    try {
	        StringBuilder stringBuilder = new StringBuilder();
	        boolean needNewLine = false;

	        while(true) {
		        String line = bufferReader.readLine();
		        if(line == null) {
		        	break;
		        }
	            if(needNewLine) {
	            	stringBuilder.append("\n");
	            }
	            needNewLine = true;
	            stringBuilder.append(line);
	        }

	        return stringBuilder.toString();
	    } finally {
	        bufferReader.close();
	    }
	}
	
	public static boolean writeTextToFile(String fileName, String content) throws Exception {
		File file = new File(fileName);

		if(file.exists()) {
			if(content.replaceAll("\\s+$", "").equals(readTextFromFile(fileName).replaceAll("\\s+$", ""))) {
				trace("Skip " + fileName);
				RunStats.countWrittenFile(false);
				return false;
			}
		}

	    BufferedWriter bufferWriter = new BufferedWriter(new FileWriter(file));
	    try {
	    	bufferWriter.write(content);
	    } finally {
	    	bufferWriter.close();
	    }

		trace("Written " + fileName);
		RunStats.countWrittenFile(true);
		return true;
	}

	public static String joinStringList(String delimiter, List<String> stringList) {
		String result = "";
		boolean isFirst = true;
		
		for(String s : stringList) {
			if(! isFirst) {
				result = result + delimiter;
			}
			isFirst = false;

			result = result + s;
		}
		
		return result;
	}

	public static String normalizeSymbol(String s) {
		return s.replaceAll("\\.", "_");
	}
	
	public static String getBaseFileName(String fileName) {
		fileName = fileName.replaceAll("\\\\", "/");
		int index = fileName.lastIndexOf('/');
		if(index >= 0) {
			fileName = fileName.substring(index + 1);
		}
		index = fileName.lastIndexOf('.');
		if(index >= 0) {
			fileName = fileName.substring(0, index);
		}
		
		return fileName;
	}
	
	public static List<CppClass> sortClassList(List<CppClass> classList) {
		List<CppClass> newList = new ArrayList<CppClass>();
		newList.addAll(classList);
		Collections.sort(newList, new Comparator<CppClass>() {

			@Override
			public int compare(CppClass o1, CppClass o2) {
				return o1.getQualifiedName().compareTo(o2.getQualifiedName());
			}
		}
		);
		return newList;
	}

	public static List<String> sortStringList(List<String> stringList) {
		List<String> newList = new ArrayList<String>();
		newList.addAll(stringList);
		Collections.sort(newList);
		return newList;
	}

	public static String upcaseFirst(String s)
	{
		if(s.length() <= 1) {
			return s.toUpperCase();
		}
		else {
			return s.substring(0, 1).toUpperCase() + s.substring(1);
		}
	}

	public static String concatFileName(String path, String fileName) {
		return new File(path, fileName).getAbsolutePath();
	}

	public static void forceCreateDirectories(String path) {
		(new File(path, "")).mkdirs();
	}

	public static String generateBaseClassList(List<DeferClass> baseClassList) {
		String typeName = "";

		for(DeferClass deferClass : baseClassList) {
			if(deferClass.getVisibility() == EnumVisibility.Public) {
				typeName = typeName + ", " + deferClass.getName();
			}
		}
		
		return typeName;
	}

	public static <T> void swapListItems(List<T> list, int a, int b) {
		T temp = list.get(a);
		list.set(a, list.get(b));
		list.set(b, temp);
	}

	public static <T> int findInArray(T[] array, T item) {
		for(int i = 0; i < array.length; ++i) {
			if(array[i].equals(item)) {
				return i;
			}
		}

		return -1;
	}

	public static <T> void addToList(List<T> list, T item) {
		if(item == null) {
			return;
		}

		for(T d : list) {
			if(d.equals(item)) {
				return;
			}
		}

		list.add(item);
	}

}
