<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<meta http-equiv = "content-type" content = "text/html; charset = utf-8"/>
	<meta name="author" content="杨美琦、吴振鹏"/>
	<title>全部系别 - 教授 - 师资队伍 - 中国人民大学信息学院</title>

	<link rel="stylesheet" type="text/css" href="css/common.css"/>
	<link rel="stylesheet" type="text/css" href="css/academic_faculty.css"/>
	
	<script type="text/javascript" src="js/jquery-1.11.1.min.js"></script>
	<script type="text/javascript" src="js/menu.js"></script>
	<script type="text/javascript">
	$(document).ready(function() {
		$("#main .content .check_boxx .text").click(function() {
			$(this).siblings().removeClass('click');
			$(this).addClass('click');
			var teacher_dept=$("#main .content .check_box0").find("div.click").find('input').val();
			var url = '';
			if(teacher_dept==0) url='academic_faculty.php';
			if(teacher_dept==1) url='academic_direction.php';
			location.href = url;
		});

		$("#main .content .check_box .text").click(function() {
			$(this).siblings().removeClass('click');
			$(this).addClass('click');
			var teacher_dept=$("#main .content .check_box1").find("div.click").find('input').val();
			var teacher_type=$("#main .content .check_box2").find("div.click").find('input').val();
			var url = 'academic_faculty.php?teacher_dept='+teacher_dept+'&teacher_type='+teacher_type;
			location.href = url;
		});
	});
	</script>
	
</head>
<body>
	<!--头部-->

    <script type="text/javascript">
        curMenu = 5;
        window.onload = displayCurrent;
        $(function(){
			$("#search").click(function(){
				$("#form").submit();
			});
        });
    </script>
	<div id="top">
		<div class="top_box">
			<!--顶部-->
			<div class="header">
				<div class="logo"><a href="index.php"><img src="images/top_logo.jpg"/></a></div>
				<div class="link"><a href="overview_contact.php">联系我们 </a>|<a href="mailto:rucinfo@ruc.edu.cn"> 院长信箱 </a>|<a href="en/index.php"> English </a>|<a href="teacherlogin.html"> 教师入口 </a></div>
				<div class="search">
					<form id="form" method="get" action="search_news.php">
						<input class="input" name="name" id="name" type="text" value="输入关键字" onblur="if(this.value==''){this.value='输入关键字';$(this).css({color:'#BBBBBB'})}" onfocus="if(this.value=='输入关键字'){this.value='';$(this).css({color:'#000000'})}" style="color:#BBBBBB" name="name"/>
						<img class="button" id ="search" src="images/top_search.png"/>
					</form>
				</div>
			</div>
			<!--导航菜单-->
			<div class="menu">
				<div class="menu_separator_box">
					<div class="menu_separator1"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator2"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator3"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator4"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator5"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator6"><img src="images/menu_separator.png"/></div>
					<div class="menu_separator7"><img src="images/menu_separator.png"/></div>
				</div>
				

				<div id="menu_red_bg"></div>
				<div class="menu_text_box">
					<div class="menu_text" onmouseover="mouseOver(1)" onmouseout="mouseOut(1)"><div class="text"><a id="menu_text1" href="index.php">首&nbsp&nbsp&nbsp&nbsp&nbsp页</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(2)" onmouseout="mouseOut(2)"><div class="text"><a id="menu_text2" href="overview_intro.php">学院概况</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(3)" onmouseout="mouseOut(3)"><div class="text"><a id="menu_text3" href="news_list.php">新闻公告</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(4)" onmouseout="mouseOut(4)"><div class="text"><a id="menu_text4" href="education.php">人才培养</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(5)" onmouseout="mouseOut(5)"><div class="text"><a id="menu_text5" href="academic_faculty.php">师资科研</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(6)" onmouseout="mouseOut(6)"><div class="text"><a id="menu_text6" href="student.php">学生发展</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(7)" onmouseout="mouseOut(7)"><div class="text"><a id="menu_text7" href="internation_news.php">对外交流</a></div></div>
					<div class="menu_text" onmouseover="mouseOver(8)" onmouseout="mouseOut(8)"><div class="text"><a id="menu_text8" href="alumni.php">院友之家</a></div></div>
				</div>
			</div>
		</div>
	</div>

	<!--导航子菜单-->
	<div id="child_menu">
		<div id="banner_shadow"></div>
		<div class="child_menu_box">
			<div id="child_menu2" onmouseover="menuMouseOver(2)" onmouseout="menuMouseOut(2)">
				<div class="item"><a href="overview_intro.php">学院简介</a></div>
				<div class="item"><a href="overview_dean.php">院长寄语</a></div>
				<div class="item"><a href="overview_leadership.php">现任领导</a></div>
				<div class="item"><a href="overview_structure.php">机构设置</a></div>
                <div class="item"><a href="overview_contact.php">联系我们</a></div>
			</div>
			<div id="child_menu3" onmouseover="menuMouseOver(3)" onmouseout="menuMouseOut(3)">
				<div class="item"><a href="news_list.php">学院新闻</a></div>
				<div class="item"><a href="notice_list.php">学院公告</a></div>
				<div class="item"><a href="album_list.php">信息相册</a></div>
				<div class="item"><a href="focus_list.php">新闻人物</a></div>
				<div class="item"><a href="video_list.php">信息影像</a></div>
			</div>
			<div id="child_menu4" onmouseover="menuMouseOver(4)" onmouseout="menuMouseOut(4)">
                <div class="item"><a href="education_degree.php?id=1">本科生</a></div><div class="item"><a href="education_degree.php?id=2">学术型硕士</a></div><div class="item"><a href="education_degree.php?id=3">全日制工程硕士</a></div><div class="item"><a href="education_degree.php?id=4">博士生</a></div><div class="item"><a href="education_degree.php?id=5">在职工程硕士</a></div><div class="item"><a href="education_degree.php?id=6">同等学力</a></div>				<div class="item"><a href="education_notice.php">教育公告</a></div>
			</div>
			<div id="child_menu6" onmouseover="menuMouseOver(6)" onmouseout="menuMouseOut(6)">
				<div class="item"><a href="party_notice_list.php">学生党建</a></div>
				<div class="item"><a href="youth_news_list.php">团学风采</a></div>
				<div class="item"><a href="employ_list.php">就业实习</a></div>
				<div class="item"><a href="affair_list.php">学生事务</a></div>
				<div class="item"><a href="scholarship_list.php">奖励资助</a></div>
			</div>
			<div id="child_menu5" onmouseover="menuMouseOver(5)" onmouseout="menuMouseOut(5)">
				<div class="item"><a href="academic_faculty.php">师资队伍</a></div>
				<div class="item"><a href="academic_research.php">学术科研</a></div>
			</div>
			<div id="child_menu7" onmouseover="menuMouseOver(7)" onmouseout="menuMouseOut(7)">
				<div class="item"><a href="internation_news.php">外事新闻</a></div>
				<div class="item"><a href="internation_info.php">交流信息</a></div>
				<div class="item"><a href="internation_project.php">合作项目</a></div>
				<div class="item"><a href="internation_guide.php">办事指南</a></div>
				<div class="item"><a href="internation_journal.php">交流简报</a></div>
				<div class="item"><a href="internation_experience.php">交流心得</a></div>
			</div>
			<div id="child_menu8" onmouseover="menuMouseOver(8)" onmouseout="menuMouseOut(8)">
				<div class="item"><a href="alumni_news.php">院友新闻</a></div>
				<div class="item"><a href="alumni_mien.php">院友风采</a></div>
				<div class="item"><a href="alumni_namelist.php">院友名录</a></div>
				<div class="item"><a href="alumni_journal.php">信息骄子</a></div>
			</div>
		</div>
	</div>
    
    
        <!-- banner图片 -->
	<div id="banner_pic">
		<div class="pic"><img src="images/intro/banner.jpg"/></div>
	</div>
    	<!--主体-->
	<div id="main">
		<!--左侧sidebar-->
			<script type="text/javascript">
		$(window).load(function() { 
				if (1==0)
				$("#sub_academic").slideToggle("slow");
		}); 
	</script>
        <div class="side_bar">
			<div class="side_top"><a class="logo" href="academic_faculty.php"><img src="images/side_logo/6.png" /></a></div>
            <span style="cursor:pointer"><div class="side_menu"
				id="cur_menu">
				<div class="text" name="faculty" id="faculty"><a href="academic_faculty.php">师资队伍</a></div>
			</div></span>
            <span style="cursor:pointer"><div class="side_menu"
				>
				<div class="text" name="academic" id="academic"><a href="academic_research.php">学术科研</a></div>
			</div></span>
			<div class="sub_menu_box" id="sub_academic" name="sub_academic"
			style="display:none">
				<div class="sub_menu"><div class="text" 
					>
					<a href="academic_news_list.php">科研动态</a></div></div>
				<div class="sub_menu"><div class="text"
					>
					<a href="academic_notice_list.php?type=5">科研成果</a></div></div>
				<div class="sub_menu"><div class="text">
					<a href="#kytd">科研团队</a></div></div>
				<div class="sub_menu"><div class="text"
					>
					<a href="academic_lecture_list.php">讲座信息</a></div></div>
			</div>
        </div>		<!--右侧上方导航条-->
		<div class="navigation"><div class="text">您所在的位置：<a href="academic_faculty.php">师资科研</a> > <a href="academic_faculty.php">师资队伍</a></div></div>
		<!--右侧内容-->
		<div class="content">
			<!--选择框-->
			<div class="check_boxx">
				<div class="check_box0">
					<div class="front">查询模式：</div>
					<div class="choices">
						<div class="text click">按教学机构查询<input type="hidden" value="0"/></div>
						<div class="text ">按导师专业查询<input type="hidden" value="1"/></div>
					</div>
				</div>
			</div>
			<div class="check_box">
				<div class="check_box1">
					<div class="front">教学机构：</div>
					<div class="choices">
						<div class="text  click">不限<input type="hidden" value="0"/></div>
						<div class="text">经济信息管理系<input type="hidden" value="1"/></div><div class="text">计算机科学与技术系<input type="hidden" value="2"/></div><div class="text">数学系<input type="hidden" value="3"/></div><div class="text">信息技术基础教研室<input type="hidden" value="4"/></div><div class="text">公共数学教研室<input type="hidden" value="5"/></div>					</div>
				</div>
				<div class="check_box2">
					<div class="front">职　　称：</div>
					<div class="choices">
						<div class="text ">不限<input type="hidden" value="0"/></div>
						<div class="text click">教授<input type="hidden" value="3"/></div><div class="text">副教授<input type="hidden" value="2"/></div><div class="text">讲师<input type="hidden" value="1"/></div><div class="text">兼职教授<input type="hidden" value="4"/></div><div class="text">客座教授<input type="hidden" value="6"/></div><div class="text">师资博士后<input type="hidden" value="7"/></div>					</div>
					<div class="black_line"></div>
				</div>
			</div>
			<!--教师卡片-->
			<div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=56" target="_blank"><img src="/userfiles/teacher/20150101182337978.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=56"  target="_blank">陈红（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>大数据管理与隐私保护、基于新硬件的数据管理与数据分析、数据仓库与数据挖...</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p></p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=57" target="_blank"><img src="/userfiles/teacher/20150101182633279.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=57"  target="_blank">杜小勇（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>数据管理技术、语义网技术、智能信息检索技术；</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p></p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=58" target="_blank"><img src="/userfiles/teacher/20150101182930188.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=58"  target="_blank">何军（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>近年主要研究方向为数据挖掘、数据库、信息检索、商务智能、社交网络分析与...</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p></p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=85" target="_blank"><img src="/userfiles/teacher/20160918051921620.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=85"  target="_blank">柯媛元（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>具退化性及奇异性的非线性扩散方程。</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p></p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=59" target="_blank"><img src="/userfiles/teacher/20150101183131910.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=59"  target="_blank">李翠平（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>长期从事数据库教学与科研工作，目前研究方向为社会网络分析、社会推荐、大数...</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p>1. 硕士生课程：数据仓库与数据挖掘、2. 硕士生课程：非结构化大数据分析、3. ...</p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=60" target="_blank"><img src="/userfiles/teacher/20150502225626682.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=60"  target="_blank">李德英（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>无线传感器网络、物联网、社会网络、算法设计与分析</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p>离散数学、图论、运筹学</p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=27" target="_blank"><img src="/userfiles/teacher/20150101165542515.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=27"  target="_blank">梁彬（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>1. 软件系统安全性分析，核心问题是软件系统安全漏洞及缺陷的检测，将综合采用...</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p></p></div>
						</div><div class="card">
							<div class="photo"><a href="academic_professor.php?teacher_id=79" target="_blank"><img src="/userfiles/teacher/20150101204727910.jpg"></a></div><div class="name"><a href="academic_professor.php?teacher_id=79"  target="_blank">梁循（教授）</a></div><div class="research"><p><b>研究方向</b></p><p>社交网络大数据、智慧城市计算、机器学习、商务智能信息系统、互联网金融、...</p></div>
						<div class="courses"><p><b>讲授课程</b></p><p>《大数据物联网复杂信息系统》(经济信息管理系, 硕士1年级)、《商务建模与...</p></div>
						</div><div class="page_box"><div class="pre"><div class="img"><img src="images/news/previous.png"></div><div class="text">上一页</div></div><div class="page active"><a href="academic_faculty.php?teacher_dept=0&teacher_type=3&page=1">1</a></div><div class="page"><a href="academic_faculty.php?teacher_dept=0&teacher_type=3&page=2">2</a></div><div class="page"><a href="academic_faculty.php?teacher_dept=0&teacher_type=3&page=3">3</a></div><div class="next"><div class="text"><a href="academic_faculty.php?teacher_dept=0&teacher_type=3&page=2">下一页</a></div><div class="img"><img src="images/news/next.png"></div></div><div style="float:right">共24条数据</div></div>		</div>
	</div>

	<!-- 底部 -->
	<!-- 底部 -->
	<div id="footer">
		<div class="bottom">
			<div class="bottom_box">
					<div class="wechat">
						<div style="width:100px;">
						<img src="images/wechat.jpg" style="width:95px;margin-bottom:10px">
						公众微信二维码
						</div>
					</div>
				<div class="copy_right">Copyright © 2015 School of Information, Renmin University of China. All rights reserved.</div>
				<div class="copy_right_cn">版权所有 中国人民大学信息学院</div>
				<div class="address">地址：北京市海淀区中关村大街59号</div>
				<div class="email">邮编：100872</div>
			</div>
		</div>
	</div>
	<div style="display:none;">
		<script type="text/javascript">
			var cnzz_protocol = (("https:" == document.location.protocol) ? " https://" : " http://");
			document.write(unescape("%3Cspan id='cnzz_stat_icon_1254120420'%3E%3C/span%3E%3Cscript src='" + cnzz_protocol + "s11.cnzz.com/z_stat.php%3Fid%3D1254120420' type='text/javascript'%3E%3C/script%3E"));
		</script>
	</div></body>
</html>